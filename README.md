# rntop
A top-like tool for monitoring GPUs across a cluster.

## Installation
Running `runtop` is possible with [Docker](https://docs.docker.com/get-docker/).

In the future there will be native installations for Linux distributions.

## Running
#### Setup
`rntop` uses SSH connections for monitoring the remote GPU machines.
Therefore, it is necessary that you will have SSH access to all machines you want to monitor.

Connecting with password is not supported at the moment so [set up](https://superuser.com/a/8110) your SSH configuration to work with SSH keys if needed.

> You can verify the SSH connection to a GPU machine by running `ssh user@server nvidia-smi`

#### Execution
Run `rntop` using the following command and place the machine hostnames or IPs instead of the `...` placeholder:
```
docker run -it --rm -v $HOME/.ssh:/root/.ssh runai/rntop ...
```

#### Passing a username
It is possible to specify a username for the connections.

If you are using the same username for all machines pass it as the argument `--username`.
If you are using different usernames for different machines you can pass them as part of the hostname (e.g. `john@server`).

Note that we mount the SSH directory from the host to the container so that it would be able to use the SSH configuration file and keys to establish the SSH connections.

#### Examples
Here are some examples of commands (`...` is used for simplification):
1. `docker run ... runai/rntop john@192.168.1.60`
2. `docker run ... runai/rntop --username john 192.168.1.60 192.168.1.61 rob@192.168.1.62`

> Pass `--help` to see all the available arguments.

## Troubleshooting
### SSH
`rntop` uses [libssh](https://www.libssh.org/) for the SSH connections by default.
If you are encountering SSH connection problems try using the native `ssh` agent by passing the argument `--ssh` to the `rntop` command.

### Bugs
Please open a [GitHub issue](https://github.com/run-ai/rntop/issues) in case you encounter a bug.
To help us in fixing the issue please describe the scenario well and provide any needed information.

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
