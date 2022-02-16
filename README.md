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

### Develop
#### Build
```
bazel build //...
```

### Lint
```
cpplint --recursive .
```

#### Run
```
bazel run :rntop
```
> Pass arguments is possible with using `--` as a delimeter; e.g. `bazel run :rntop -- --help`

### References
* Set up SSH to work without password: https://superuser.com/a/8110
