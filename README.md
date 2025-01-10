The main part of this (for now) small project is to show case how Muons can be used to investigate the inner composition of materials. 

The fun part can be found in `notebook/` there I show how to use the flux of muons to infer the density of a material. I also show how can a muon flux be used to inspect the inner structure of a solid object. 

 This is still work in progress so I expect to have a better documentation in the future. In order to run it you just need to install the typical `numpy`, `scipy` and `pandas`. No big deal with conda/mamba.

If you want to repdroduce my simulation just go ahead and build thi project. For that I installed geant4 with conda within an  env called `g4`:
```
mamba install -c conda-forge geant4
```
Then you need to create a `build` folder and enter the following recipe (sometimes cmake won't know where to look for Geant4... )
```
cmake -DZLIB_ROOT=$CONDAROOT/envs/g4  -DZLIB_INCLUDE_DIR=$CONDAROOT/envs/g4/include  -DZLIB_LIBRARY=$CONDAROOT/envs/g4/lib/libz.1.3.1.dylib  .. && make
```

If you want to change the saturation of your material just go to `src/construccion.cc` and modify the proper line. You can play around with the configuration of the generator too in `src/generator.cc`. In general there's plenty to play with.

Cheers.
