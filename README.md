# Historical Butterfly Counting

This repository contains C++ codes and datasets for the paper:

> Efficient Historical Butterfly Counting in Large Temporal Bipartite Networks via Graph Structure-aware Index

**Please refer our technical report if you are interested in the paper detailes.**

## Datasets

Real-world datasets:

| Dataset | Download link                                                |
| ------- | ------------------------------------------------------------ |
| WQ      | [Link](http://konect.cc/networks/edit-bnwikisource/)         |
| WN      | [Link](http://konect.cc/networks/edit-itwikinews/)           |
| SO      | [Link](http://konect.cc/networks/stackexchange-stackoverflow/) |
| CU      | [Link](http://konect.cc/networks/citeulike-ti/)              |
| BS      | [Link](http://konect.cc/networks/bibsonomy-2ti/)             |
| TW      | [Link](http://konect.cc/networks/munmun_twitterex_ut/)       |
| AM      | [Link](http://konect.cc/networks/amazon-ratings/)            |
| ER      | [Link](http://konect.cc/networks/edit-ruwiktionary/)         |
| EV      | [Link](http://konect.cc/networks/edit-viwiki/)               |
| WT      | [Link](http://konect.cc/networks/edit-enwiktionary/)         |

## How to Run the Codes

### Compilation and Running

After cloning the codes, use the following command to compile the codes in the repository :

```sh
make app
```

Then you can use the following command to run the program on `toy_data.txt` :

```sh
make test
```

or

```sh
./app < toy_data.txt
```

The program read the dataset from `stdin` and generate queries automatically, then it will output queries and answers to `stdout` and output the time usage to `stderr`.

The dataset should be in the following format:

1. The first line contains a integer $m$, which means the number of edges.
2. Each line of the following $m$ lines should have $2$ positive integers $u,v$ and a real number $t$, which mean an edge.

You can modify the generation method of the queries in `query.h`.

### Command Line Parameters

A general command of our program is like:

```sh
./app [-option1=value1] [-option2=value2] ...
```

There are two options for you :

| Parameters | Description       |
| :--------- | :---------------- |
| -thrs      | Number of threads |
| -maxM      | Space usage (GB)  |

Actual space usage generally sticks to the paramter, `maxM`, with minor difference.