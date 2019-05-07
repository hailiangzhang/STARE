# Build STARE. Note: This container can be slimmed down by removing the stuff
# that was used to build STARE.
FROM centos:centos7.6.1810

# Pick a branch (or commit) in the STARE repository
ARG STARE_BRANCH=master

# install the EPEL repo
RUN yum -y install https://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm

# things that are useful, but can be removed when everything is working
RUN yum -y install which  && \
    yum -y install doxygen  && \
    yum -y install wget

# install useful things
RUN yum -y install git && \
    yum -y install csh && \
    yum -y install make && \
    yum -y install gcc-c++ && \
    yum -y install gcc && \
    yum -y install cmake3.x86_64 && \
    yum -y install python36 && \
    yum -y install python36-devel.x86_64 && \
    yum -y install boost169-devel.x86_64
 
 RUN yum -y install python36-pip.noarch && \
     pip3.6 install --upgrade pip && \
     pip3.6 install numpy

# make a directory to work in
RUN mkdir /root/stare/
RUN mkdir /root/stare/STARE/
 
# move there
WORKDIR /root/stare/
 
# get CUTE unit test framework
RUN git clone https://github.com/PeterSommerlad/CUTE.git
 
# clone STARE
# RUN git clone --single-branch --branch ${STARE_BRANCH} https://github.com/hailiangzhang/STARE.git
COPY ./CMakeLists.txt /root/stare/STARE/
COPY ./src/ /root/stare/STARE/src/
COPY ./include/ /root/stare/STARE/include/
COPY ./app/ /root/stare/STARE/app/
COPY ./tests/ /root/stare/STARE/tests/

# tell the build where CUTE is
ENV CUTE_INCLUDE_DIR=/root/stare/CUTE
 
# compile/install
RUN mkdir /root/stare/build
WORKDIR /root/stare/build 

# cmake3's FindBoost doesn't see the shared object libraries with all the 
# version stuff.
RUN ln -s /usr/lib64/libboost_python34.so.1.69.0 /usr/lib64/libboost_python3.so && \
    ln -s /usr/lib64/libboost_numpy34.so.1.69.0 /usr/lib64/libboost_numpy3.so

# Use environment variables to tell stare where to find stuff related to 
# compiling with the boost library
ENV BOOST_INCLUDEDIR /usr/include/boost169
ENV BOOST_LIBRARYDIR /usr/lib64
ENV Python_LIBRARY_DIR /usr/lib/python3.6/site-packages
ENV BOOST_PYTHON_INCLUDE_DIR /usr/include/python3.6m

RUN cmake3 ../STARE  && \
     make && \
     make install
 
# copy testing script to stare home folder
COPY ./docker_files/test.py /root/stare/

# switch back workdir
WORKDIR /root/

# command
CMD python3.6 /root/stare/test.py
