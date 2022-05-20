#!/bin/bash

token=`sudo docker run -it -v $(pwd):/test -d epitechcontent/epitest-docker`
sudo docker exec -it $token /bin/sh
