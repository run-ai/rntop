# rntop
A top-like tool for monitoring GPUs across a cluster.

## Development
### Setup
#### Build a Development Docker Image
```
docker build -f devel.Dockerfile -t runai/rntop:devel .
```

#### Run a Development Container
```
docker run -it --rm -v $PWD:/rntop -w /rntop -v $HOME/.ssh:/root/.ssh runai/rntop:devel
```
> Add `-v /var/run/docker.sock:/var/run/docker.sock` if you also want to build Docker images

### Develop
#### Build
```
bazel build //...
```

#### Lint
```
cpplint --recursive .
```

#### Run
```
bazel run :rntop
```
> Pass arguments is possible with using `--` as a delimeter; e.g. `bazel run :rntop -- --help`

#### Build Docker Image
First of all build the application; it's recommended to build with optimizations with the command:
```
bazel build :rntop -c opt
```

Now build the Docker image itself with the command:
```
docker build -f Dockerfile -t runai/rntop:beta bazel-bin
```

### References
* Set up SSH to work without password: https://superuser.com/a/8110
