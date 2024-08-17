IMAGE_NAME = blog-backend
IMAGE_VERSION = v1
PORT = 10040
DEPOSITORY_PATH = ccr.ccs.tencentyun.com/lsm1998

stop:
	@echo "Stopping container..."
	@docker ps -q -f name=$(IMAGE_NAME) | grep -q . && docker rm -f $(IMAGE_NAME) || true

clear:
	@echo "Removing image..."
	docker images | grep -E "$(IMAGE_NAME)" | awk '{print $$3}' | uniq | xargs -I {} docker rmi --force {}

build:
	@echo "Building image..."
	docker build -t $(IMAGE_NAME):$(IMAGE_VERSION) .

tag:
	docker tag $(IMAGE_NAME):$(IMAGE_VERSION) $(DEPOSITORY_PATH)/$(IMAGE_NAME):$(IMAGE_VERSION)
	docker push $(DEPOSITORY_PATH)/$(IMAGE_NAME):$(IMAGE_VERSION)

run:
	@echo "Starting container..."
	docker run -d --name $(IMAGE_NAME) -p $(PORT):$(PORT) $(IMAGE_NAME):$(IMAGE_VERSION)

.PHONY: stop clear build tag run all