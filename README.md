# Historical Butterfly Counting

This repository contains C++ codes and datasets for the paper:

> Efficient Historical Butterfly Counting in Large Temporal Bipartite Networks via Graph Structure-aware Index

The attached technical report mainly contains omitted proofs and details from our main submission due to the 12-page limit. We implement the graph structure-aware index (GSI) method that first proposed in the paper.

Note that we have compared our method with the BFC-VP++, [WPS](https://github.com/CUHK-DBGroup/SIGMOD24-Butterfly-Bi-Triangle-Counting), and [TBC++](https://github.com/ZJU-DAILY/TBFC), where WPS and TBC++ are open-source. The code of BFC-VP++ was obtained from their authors.

### 📚 Introduction
In this paper, we study counting butterflies on temporal bipartite graphs for certain time-windows, known as the historical butterfly counting problem. This problem enables in-depth trend and dynamics analysis over temporal graphs and helps understand how temporal variations influence network structures over time. To solve this problem efficiently, we propose the Graph Structure-aware Index (GSI), which supports efficient counting queries with a controllable balance between query time and memory usage. Theoretically, we prove that the GSI approach transcends conventional computational complexity barriers associated with general graphs when applied to power-law graphs. When memory becomes the bottleneck and exact counting is not required, we propose an index compression strategy to provide fast, high-quality, and unbiased approximations of the counts based on the compressed index. Our experimental results demonstrate that our query algorithm achieves up to five orders of magnitude speedup over the state-of-the-art solutions with manageable memory footprints.



### 🚀 Quick Start
#### 1. Environment requirements

```
gcc version >= 7.3.1
```
#### 2. How to compile
```
cd ./src && make
```

#### 3. File Description
```app.cpp``` Program entrance and argument parsing.
```butterfly*.h, blockStruct.h``` Implementation of the framework of index algorithms.
```PartTree.h, SegTree.h``` Implementation of Chazelle’s structure.
```query.h``` Implementation of query algorithms.

#### 4. Parameters
``` -thrs [INT] ``` : number of threads for parallelized setting.
``` -maxM [INT] ``` : maximum memory usage (GB) for space-time trade-off experiments (**Section 6.3**).

###  📊 Run
Run the main experiment (**Section 6.1**) on `toydata.txt` by the following command:
```
./src/app < ./src/toydata.txt
```

Run the TBC++-comparison experiment (**Section 6.2**) on `toydata.txt` by the following command:
```
./src/tbc < ./src/toydata.txt
```

### 🗃️ Dataset 

Please take a look at the real-world datasets used in our experiments using the following links.


| Dataset | Download link |
| - | - |
| WQ | [Link](http://konect.cc/networks/edit-bnwikisource/) |
| WN | [Link](http://konect.cc/networks/edit-itwikinews/) |
| SO | [Link](http://konect.cc/networks/stackexchange-stackoverflow/) |
| CU | [Link](http://konect.cc/networks/citeulike-ti/) |
| BS | [Link](http://konect.cc/networks/bibsonomy-2ti/) |
| TW | [Link](http://konect.cc/networks/munmun_twitterex_ut/) |
| AM | [Link](http://konect.cc/networks/amazon-ratings/) |
| ER | [Link](http://konect.cc/networks/edit-ruwiktionary/) |
| EV | [Link](http://konect.cc/networks/edit-viwiki/) |
| WT | [Link](http://konect.cc/networks/edit-enwiktionary/) |

###  ✉️ Contact

If you have any questions about the code or find any errors, please list them in the `issue` or contact me directly by email: ```qiuyangmang@link.cuhk.edu.cn```.
