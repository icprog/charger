FROM hypriot/rpi-python
MAINTAINER john_clayton@me.com

EXPOSE 5000

COPY requirements.txt /
RUN pip install -r /requirements.txt

COPY docker-entrypoint.sh / 
RUN chmod +x /docker-entrypoint.sh 

CMD [ "/docker-entrypoint.sh" ]


