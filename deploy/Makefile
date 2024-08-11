IMAGE_NAME = blog-backend
IMAGE_VERSION = v1
PORT = 10040
DEPOSITORY_PATH = ccr.ccs.tencentyun.com/lsm1998

stop:
	docker rm -f $(IMAGE_NAME) || true

clear:
	docker images | grep -E "$(IMAGE_NAME)" | awk '{print $$3}' | uniq | xargs -I {} docker rmi --force {}

build:
	docker build -t $(IMAGE_NAME):$(IMAGE_VERSION) .

tag:
	docker tag $(IMAGE_NAME):$(IMAGE_VERSION) $(DEPOSITORY_PATH)/$(IMAGE_NAME):$(IMAGE_VERSION)
	docker push $(DEPOSITORY_PATH)/$(IMAGE_NAME):$(IMAGE_VERSION)

run:
	docker run -d --name $(IMAGE_NAME) -p $(PORT):$(PORT) $(IMAGE_NAME):$(IMAGE_VERSION)

all:
	stop
	clear
	build
	tag
	run