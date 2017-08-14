# lhcb-alp

Code to obtain the upper limit shown in [arXiv:1508.04094](https://arxiv.org/abs/1508.04094).

## Prerequisites

* C++ compiler supporting C++14 features,
* [ROOT](https://root.cern.ch): check whether `root-config` is in your `PATH`.

## Usage

Download [`LHCb-PAPER-2015-036-figures.zip`](https://cds.cern.ch/record/2045144/files/LHCb-PAPER-2015-036-figures.zip) and put `lhcb_2015_035.root` into [`data`](data) directory. Then, run `make` to get `bin/lhcb-alp`.

The input must have three columns in units of `log10(m_a / MeV)`, `log10(f_a / GeV)`, and `log10(tau_a / ps)`, where `m_a` is the ALP mass, `f_a` is the decay constant, and `tau_a` is the lifetime. If the name of input file is `input.dat`, run

```
./bin/lhcb_bound input.dat output.dat
```

The `output.dat` will have four columns, where the first three are the same as the input and the last column corresponds to the upper limit extracted from `lhcb_2015_035.root`.
