cmd_Release/obj.target/cryptonote/src/crypto/keccak.o := cc -o Release/obj.target/cryptonote/src/crypto/keccak.o ../src/crypto/keccak.c '-DNODE_GYP_MODULE_NAME=cryptonote' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-DV8_DEPRECATION_WARNINGS' '-DV8_IMMINENT_DEPRECATION_WARNINGS' '-D_GLIBCXX_USE_CXX11_ABI=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-D__STDC_FORMAT_MACROS' '-DOPENSSL_NO_PINSHARED' '-DOPENSSL_THREADS' '-DBUILDING_NODE_EXTENSION' -I/home/less/.cache/node-gyp/18.20.4/include/node -I/home/less/.cache/node-gyp/18.20.4/src -I/home/less/.cache/node-gyp/18.20.4/deps/openssl/config -I/home/less/.cache/node-gyp/18.20.4/deps/openssl/openssl/include -I/home/less/.cache/node-gyp/18.20.4/deps/uv/include -I/home/less/.cache/node-gyp/18.20.4/deps/zlib -I/home/less/.cache/node-gyp/18.20.4/deps/v8/include -I../src -I../src/contrib/epee/include -I../src/contrib/variant/include -I../../nan  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -O3 -fno-omit-frame-pointer  -MMD -MF ./Release/.deps/Release/obj.target/cryptonote/src/crypto/keccak.o.d.raw   -c
Release/obj.target/cryptonote/src/crypto/keccak.o: ../src/crypto/keccak.c \
 ../src/crypto/hash-ops.h ../src/common/int-util.h \
 ../src/contrib/epee/include/warnings.h ../src/crypto/keccak.h
../src/crypto/keccak.c:
../src/crypto/hash-ops.h:
../src/common/int-util.h:
../src/contrib/epee/include/warnings.h:
../src/crypto/keccak.h:
