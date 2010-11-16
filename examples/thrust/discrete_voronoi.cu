#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/tuple.h>
#include <thrust/extrema.h>
#include <thrust/iterator/counting_iterator.h>
#include <iostream>

#include <iomanip>
#include <stdio.h>
#include <cmath>
#include <carbon/lambda.hpp>

using namespace carbon::lambda;

// Compute an approximate Voronoi Diagram with a Jump Flooding Algorithm (JFA)
//
// References
//   http://en.wikipedia.org/wiki/Voronoi_diagram
//   http://www.comp.nus.edu.sg/~tants/jfa.html
//   http://www.utdallas.edu/~guodongrong/Papers/Dissertation.pdf
//
// Thanks to David Coeurjolly for contributing this example



// minFunctor
// Tuple  = <seeds,seeds + k,seeds + m*k, seeds - k, 
//           seeds - m*k, seeds+ k+m*k,seeds + k-m*k,
//           seeds- k+m*k,seeds - k+m*k, i>

struct minVoro_impl {
  template<typename, typename, typename, typename, typename, typename>
  struct result { typedef int type; };

  __host__ __device__
  int operator()(int x_i, int y_i, int p, int q, int m, int n) const
  {    
    if (q == m*n)
      return p;

    // coordinates of points p and q
    int y_q =  q / m;
    int x_q =  q - y_q * m;
    int y_p =  p / m;
    int x_p =  p - y_p * m;
        
    // squared distances
    int d_iq = (x_i-x_q) * (x_i-x_q) + (y_i-y_q) * (y_i-y_q);
    int d_ip = (x_i-x_p) * (x_i-x_p) + (y_i-y_p) * (y_i-y_p);

    if (d_iq < d_ip)
      return q;  // q is closer
    else
      return p;
  }
};

function<minVoro_impl> const minVoro_;

struct minFunctor
{
  int k,m,n;
  
  __host__ __device__
    minFunctor(int _m,int _n,int _k) : n(_n),m(_m),k(_k) {}


  //To decide I have to change my current Voronoi site
  __host__ __device__
      int minVoro(int x_i, int y_i, int p, int q)
      {    
          if (q == m*n)
              return p;

          // coordinates of points p and q
          int y_q =  q / m;
          int x_q =  q - y_q * m;
          int y_p =  p / m;
          int x_p =  p - y_p * m;
        
          // squared distances
          int d_iq = (x_i-x_q) * (x_i-x_q) + (y_i-y_q) * (y_i-y_q);
          int d_ip = (x_i-x_p) * (x_i-x_p) + (y_i-y_p) * (y_i-y_p);

          if (d_iq < d_ip)
              return q;  // q is closer
          else
              return p;
      }

  //For each point p+{-k,0,k}, we keep the Site with minimum distance
  template <typename Tuple>
  __host__ __device__
  int operator()(const Tuple &t)
  {
      //Current point and site
      int i = thrust::get<9>(t);
      int v = thrust::get<0>(t);

      //Current point coordinates
      int y = i / m;    
      int x = i - y * m;

      if (x >= k)
      {
          v = minVoro(x, y, v, thrust::get<3>(t));

          if (y >= k)
              v = minVoro(x, y, v, thrust::get<8>(t));

          if (y + k < n)
              v = minVoro(x, y, v, thrust::get<7>(t));
      }

      if (x + k < m)
      { 
          v = minVoro(x, y, v, thrust::get<1>(t));

          if (y >= k)
              v = minVoro(x, y, v, thrust::get<6>(t));
          if (y + k < n)
              v = minVoro(x, y, v, thrust::get<5>(t));
      }

      if (y >= k)
          v = minVoro(x, y, v, thrust::get<4>(t));
      if (y + k < n)
          v = minVoro(x, y, v, thrust::get<2>(t));

      //global return
      return v;
  }
};



// print an M-by-N array
template <typename T>
void print(int m, int n, const thrust::device_vector<T>& d_data)
{
    thrust::host_vector<T> h_data = d_data;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            std::cout << std::setw(4) << h_data[i * n + j] << " ";
        std::cout << "\n";
    }
}



/********************** TIMER Functions *************/
//Global vars
cudaEvent_t start;
cudaEvent_t end;
void timer_start()
{
    cudaEventCreate(&start); 
    cudaEventCreate(&end);
    cudaEventRecord(start,0);
}

float timer_stop_and_display()
{
  float elapsed_time;
  cudaEventRecord(end, 0);
  cudaEventSynchronize(end);
  cudaEventElapsedTime(&elapsed_time, start, end);

  std::cout << "  ( "<< elapsed_time << "ms )" << std::endl;

  return elapsed_time;
}
/********************** TIMER Functions *************/



void generate_random_sites(thrust::host_vector<int> &t, int Nb, int m, int n)
{
  srand(m*n);

  for(int k = 0; k < Nb; k++)
  {
      int index = (m * n) * (rand() / (RAND_MAX + 1.0f));

      t[index] = index + 1;
  }
}

//Export the tab to PGM image format
void vector_to_pgm(thrust::host_vector<int> &t, int m, int n,char *out)
{
    FILE *f;

    f=fopen(out,"w+t");
    fprintf(f,"P2\n");
    fprintf(f,"%d %d\n 253\n",m,n);

    for(int j = 0; j < n ; j++)
    {
        for(int i = 0; i < m ; i++)
        {
            fprintf(f,"%d ",(int)(71*t[j*m+i])%253); //Hash function to map values to [0,255]
        }
    }
    fprintf(f,"\n");
    fclose(f);
}

/************Main Jfa loop********************/
// Perform a jump with step k
void jfa(thrust::device_vector<int>& in,thrust::device_vector<int>& out, unsigned int k, int m, int n)
{
   thrust::transform(
        thrust::make_zip_iterator(
            thrust::make_tuple(in.begin(), 
                               in.begin() + k, 
                               in.begin() + m*k, 
                               in.begin() - k, 
                               in.begin() - m*k, 
                               in.begin() + k+m*k,
                               in.begin() + k-m*k,
                               in.begin() - k+m*k,
                               in.begin() - k-m*k,
                               thrust::counting_iterator<int>(0))),
        thrust::make_zip_iterator(
            thrust::make_tuple(in.begin(), 
				    		   in.begin() + k, 
                               in.begin() + m*k, 
                               in.begin() - k, 
                               in.begin() - m*k, 
                               in.begin() + k+m*k,
                               in.begin() + k-m*k,
                               in.begin() - k+m*k,
                               in.begin() - k-m*k,
                               thrust::counting_iterator<int>(0)))+ n*m,
        out.begin(),
     let_(_v = get_<0>(_1)) [
       let_(_i = get_<9>(_1)) [
         let_(_y = _i/m) [
           let_(_x = _i - _y*m) [
             if_(_x >= k) [
               _v = minVoro_(_x, _y, _v, get_<3>(_1), m, n),
               if_(_y >= k) [
                 _v = minVoro_(_x, _y, _v, get_<8>(_1), m, n)
               ],
               if_(_y+k <= n) [
                 _v = minVoro_(_x, _y, _v, get_<7>(_1), m, n)
               ]
             ],
             if_(_x + k < m) [
                 _v = minVoro_(_x, _y, _v, get_<1>(_1), m, n),
               if_(_y >= k) [
                 _v = minVoro_(_x, _y, _v, get_<6>(_1), m, n)
               ],
               if_(_y+k < n) [
                 _v = minVoro_(_x, _y, _v, get_<5>(_1), m, n)
               ]
             ],
             if_(_y >= k) [
               _v = minVoro_(_x, _y, _v, get_<4>(_1), m, n)
             ],
             if_(_y+k < n) [
               _v = minVoro_(_x, _y, _v, get_<2>(_1), m, n)
             ]
           ]
         ]
       ]
     ]
     ); 
}
/********************************************/



int main(void)
{
  int m = 2048; // number of rows
  int n = 2048; // number of columns  
  int s = 1000; // number of sites
 
  //Host vector to encode a 2D image
  std::cout << "[Inititialize " << m << "x" << n << " Image]" << std::endl;
  timer_start();
  thrust::host_vector<int> seeds_host(m*n, m*n);
  generate_random_sites(seeds_host,s,m,n);
  timer_stop_and_display();

  std::cout<<"[Copy to Device]" << std::endl;
  timer_start();
  thrust::device_vector<int> seeds = seeds_host;
  thrust::device_vector<int> temp(seeds);
  timer_stop_and_display();

  //JFA+1  : before entering the log(n) loop, we perform a jump with k=1
  timer_start();
  std::cout<<"[JFA stepping]" << std::endl;
  jfa(seeds,temp,1,m,n);
  seeds.swap(temp);
 
  //JFA : main loop with k=n/2, n/4, ..., 1
  for(int k = thrust::max(m,n) / 2; k > 0; k /= 2)
  {
      jfa(seeds,temp,k,m,n);
      seeds.swap(temp);
  }
  float time = timer_stop_and_display();  
  std::cout <<"  ( " <<  seeds.size() / (1e3 * time) << " MPixel/s ) " << std::endl;
  
  std::cout << "[Device to Host Copy]" << std::endl;
  timer_start();
  seeds_host = seeds;
  timer_stop_and_display();
  
  std::cout << "[PGM Export]" << std::endl;
  timer_start();
  vector_to_pgm(seeds_host, m, n, "discrete_voronoi.pgm");
  timer_stop_and_display();

  return 0;
}

