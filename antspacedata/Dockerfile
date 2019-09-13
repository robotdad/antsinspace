FROM python:3.7-alpine as build

LABEL description="Build container for ant space data csv file generation"

RUN apk update && apk add --no-cache \ 
    autoconf build-base binutils cmake curl file gcc g++ git libgcc libtool linux-headers make musl-dev ninja tar unzip wget

COPY . /src

WORKDIR /src

RUN make

FROM python:3.7-alpine as run

LABEL description="Runtime container for ant space data csv file generation"

RUN apk update && apk add --no-cache \ 
    libstdc++

RUN pip install redis

COPY --from=build /src/antspacedata /usr/local/bin/antspacedata
COPY --from=build /src/antfilequeue.py /usr/local/bin/antfilequeue.py

WORKDIR /data

ENV numfiles 1
ENV minlines 10
ENV maxlines 100

CMD ["sh", "-c", " python /usr/local/bin/antfilequeue.py ${numfiles} ${minlines} ${maxlines}"]