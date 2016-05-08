# MPI-ACC
A benchmark suit for MPI on clusters with GPU accelerators 

MPI-ACC is a benchmark suit that I have developed for evaluating communication performance of the clusters with GPU accelerators. This benchmark currently includes 3 communication patterns: 1) 2d-5point Stencil; 2) 3D-Torus; and 3) Collective on a sub communicator and allows multiple of them to run concurrently on the CPU and/or on the GPU. 

# Installing:
Change the Makefile and set your own MPI and CUDA library paths.
Run make to install
Run make clean to delete the current installation


# Running

benchmark_name: 
        +2DSTENCIL: 
                input: 
                        -type: "cpu" or "gpu" 
                        -size 
                        -dim_wght 
                        -dim_x 
                        -dim_y 
        +3DTORUS: 
                input: 
                        -type: "cpu" or "gpu" 
                        -size 
                        -dim_wght 
                        -dim_x 
                        -dim_y 
                        -dim_z 
        +COLLSUBCOMM: 
                input: 
                        -type: "cpu" or "gpu" 
                        -size 
                        -dim_x_keep 
                        -dim_y_keep 
                        -dim_z_keep 
