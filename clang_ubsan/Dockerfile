FROM ubuntu:18.04

#CMD ["/usr/bin/R"]

# Install packages needed to build R
RUN apt update && apt install -y \
    vim g++ gfortran make libreadline-dev \
    clang lldb llvm \
    libxml2-dev libssl-dev \
    libbz2-dev \
    liblzma-dev \
    libcurl4-openssl-dev \
    wget \
  && rm -rf /var/lib/apt/lists/*

# The image doesn't set LC_TIME, LC_NUMERIC etc, which causes warnings when 
# starting R
RUN echo "LC_ALL=\"en_US.UTF-8\"" >> /etc/default/locale

# Download the R source
# Setup clang as the compiler
# Build and install R
RUN cd /tmp \
  && wget https://stat.ethz.ch/R/daily/R-devel.tar.gz \
  && tar -xzf R-devel.tar.gz \
  && cd R-devel \
  && echo "#! /bin/sh" > config.site \
  && echo "CC=\"clang -std=gnu99 -fsanitize=undefined\"" >> config.site \
  && echo "CFLAGS=\"-fno-omit-frame-pointer -O2 -Wall -pedantic -mtune=native\"" >> config.site \
  && echo "CXX=\"clang++ -fsanitize=undefined -fno-sanitize=function,vptr -fno-omit-frame-pointer\"" >> config.site \
  && ./configure --with-x=no \
  && make \
  && make install \
  && cd /tmp && rm -r /tmp/R-devel

# Install packages
RUN echo "local({ r <- getOption('repos'); r['CRAN'] <- 'https://cloud.r-project.org'; options(repos = r)})" >> \
    /usr/local/lib/R/etc/Rprofile.site \
  && echo ".libPaths('/usr/local/lib/R/site-library')" >> /usr/local/lib/R/etc/Rprofile.site \
  && Rscript -e "install.packages(c('Rcpp', 'devtools', 'BH', 'testthat', 'roxygen2'))"

# Fix some stuff in Makeconf to make sure UBSAN tests for virtual pointers are run
RUN sed -e "s/SHLIB_LIBADD =/SHLIB_LIBADD = -lubsan/g" /usr/local/lib/R/etc/Makeconf  > /usr/local/lib/R/etc/Makeconf.tmp \
  && sed -e "s/,vptr//g" /usr/local/lib/R/etc/Makeconf.tmp  > /usr/local/lib/R/etc/Makeconf \
  && rm /usr/local/lib/R/etc/Makeconf.tmp

