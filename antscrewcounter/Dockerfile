FROM python:3.7.4-slim-buster as build

LABEL description="Build container for ant sorted tiny screws counting app"

RUN apt-get update && apt-get install -y --no-install-recommends \ 
    build-essential wget \
    && rm -rf /var/lib/apt/lists/*

COPY . /src

WORKDIR /src

RUN make

FROM python:3.7.4-slim-buster as run

LABEL description="Runtime container for counting screws sorted by ants in space"

RUN apt-get update && apt-get install -y --no-install-recommends \ 
    locales \
    && rm -rf /var/lib/apt/lists/*

RUN pip install redis

# Set the locale
RUN sed -i -e 's/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/' /etc/locale.gen && \
    echo 'LANG="en_US.UTF-8"'>/etc/default/locale && \
    dpkg-reconfigure --frontend=noninteractive locales && \
    update-locale LANG=en_US.UTF-8

ENV LANG en_US.UTF-8  

COPY --from=build /src/antscrewcounter /usr/local/bin/antscrewcounter
COPY --from=build /src/antworkerqueue.py /usr/local/bin/antworkerqueue.py
COPY --from=build /src/rediswq.py /usr/local/bin/rediswq.py

WORKDIR /data

CMD ["sh", "-c", " python /usr/local/bin/antworkerqueue.py"]