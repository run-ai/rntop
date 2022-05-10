# rntop
A top-like tool for monitoring GPUs across a cluster.

## Board for `rntop`
`rntop` can [save](#output-file) information to an output file.
Afterwards, you can go to [Board for rntop](https://run-ai.github.io/rntop-board), load this file and see an analysis of the information recorded by `rntop` over time like GPU utilization across the cluster and more.

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

#### Output file
`rntop` can save metrics to a file.

> You can then open this with [Board for rntop](#board-for-rntop) to visualize the exported information such as cluster utilization and memory usage.

This is possible by specifying a path with the argument `--output`.
`rntop` would create the file if it does not already exist and append to it if it exists because of previous runs.

Make sure the file is accessible from the host so that you will be able to upload it easily.

You can use the following command and replace the `...` placeholder with the machine hostnames or IPs:
```
docker run -it --rm -v $HOME/.ssh:/root/.ssh -v $HOME/.rntop:/host runai/rntop --output /host/rntop.log ...
```

#### Examples
Here are some examples of commands (`...` is used for simplification):
1. `docker run ... runai/rntop john@192.168.1.60`
2. `docker run ... runai/rntop --username john 192.168.1.60 192.168.1.61 rob@192.168.1.62`

> Pass `--help` to see all the available arguments.

## Troubleshooting
### SSH
The next steps should guide you in how to troubleshoot `rntop` in case it fails connecting to some machine.
For the sake of the explanation let's assume you are using the credentials `user@machine`.

First, verify that the credentials are correct by running the following command:
```
ssh user@machine nvidia-smi
```

If this does _not_ work then the credentials that you are using might be wrong or you don't have a proper SSH key to connect using these credentials.

If this works it means that the credentials are correct and for some reason it's either the container that can't connect to the machine or it's the `rntop` application itself.

Let's check if we pass all the SSH keys and configuration correctly to the container by running the following command:
```
docker run -it --rm -v $HOME/.ssh:/root/.ssh --entrypoint bash runai/rntop -c "ssh user@machine nvidia-smi"
```

If this does _not_ work then you might be using an SSH agent or macOS Keychain.
Try adding one of the following to the `rntop` command depending on the OS of your machine:
* Linux: `-v $SSH_AUTH_SOCK:$SSH_AUTH_SOCK -e SSH_AUTH_SOCK=$SSH_AUTH_SOCK`
* macOS: `-v /run/host-services/ssh-auth.sock:/ssh-agent -e SSH_AUTH_SOCK=/ssh-agent`

If the command above _did_ work then it means that the container can connect to the machine and it's the `rntop` application itself that can't.

`rntop` uses [libssh](https://www.libssh.org/) for the SSH connections by default.
There is some chance that this library does not support your setup.
Therefore, try using the native `ssh` executable as a communication agent by passing the argument `--ssh` to the `rntop` command.

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
