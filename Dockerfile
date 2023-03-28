# Build command bellow:
# docker build --build-arg username=$USER --build-arg uid=`id -u $USER` .
FROM registry.access.redhat.com/ubi9-minimal:9.1.0-1793

WORKDIR /app
RUN mkdir -p /log
RUN mkdir -p /model
RUN touch /bin/ffmpeg
RUN chmod +x /bin/ffmpeg
COPY script/stt_pipeline /app/stt_pipeline

