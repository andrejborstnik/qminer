call node-gyp clean
call node-gyp configure --nodedir="C:/Users/andrejb/streamstory/node-v0.12.0" -- -DLIN_ALG_BLAS=BLAS -DLIN_ALG_LAPACKE=LAPACKE -DLIN_ALG_INCLUDE="C:/Users/andrejb/streamstory/openblas/include" -DLIN_ALG_LIB="C:/Users/andrejb/streamstory/openblas/lib/libopenblas.dll.a"
call node-gyp build
call node -e "var la = require('./indexRelease.js').la;var A = new la.Matrix({ rows: 1000, cols: 1000, random: true });var B = new la.Matrix({ rows: 1000, cols: 1000, random: true });console.time('Multiply'); var C = A.multiply(B); console.timeEnd('Multiply');"