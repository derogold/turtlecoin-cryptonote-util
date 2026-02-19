cmd_Release/obj.target/cryptonote/src/main.o := g++ -o Release/obj.target/cryptonote/src/main.o ../src/main.cc '-DNODE_GYP_MODULE_NAME=cryptonote' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-DV8_DEPRECATION_WARNINGS' '-DV8_IMMINENT_DEPRECATION_WARNINGS' '-D_GLIBCXX_USE_CXX11_ABI=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-D__STDC_FORMAT_MACROS' '-DOPENSSL_NO_PINSHARED' '-DOPENSSL_THREADS' '-DBUILDING_NODE_EXTENSION' -I/home/less/.cache/node-gyp/18.20.4/include/node -I/home/less/.cache/node-gyp/18.20.4/src -I/home/less/.cache/node-gyp/18.20.4/deps/openssl/config -I/home/less/.cache/node-gyp/18.20.4/deps/openssl/openssl/include -I/home/less/.cache/node-gyp/18.20.4/deps/uv/include -I/home/less/.cache/node-gyp/18.20.4/deps/zlib -I/home/less/.cache/node-gyp/18.20.4/deps/v8/include -I../src -I../src/contrib/epee/include -I../src/contrib/variant/include -I../../nan  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -O3 -fno-omit-frame-pointer -std=gnu++17 -std=c++14 -fexceptions -frtti -MMD -MF ./Release/.deps/Release/obj.target/cryptonote/src/main.o.d.raw   -c
Release/obj.target/cryptonote/src/main.o: ../src/main.cc \
 /home/less/.cache/node-gyp/18.20.4/include/node/node.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/cppgc/common.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8config.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-array-buffer.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-local-handle.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-internal.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-version.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8config.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-object.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-maybe.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-persistent-handle.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-weak-callback-info.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-primitive.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-data.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-value.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-traced-handle.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-container.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-context.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-snapshot.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-date.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-debug.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-script.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-message.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-exception.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-extension.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-external.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-function.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-function-callback.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-template.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-memory-span.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-initialization.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-callbacks.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-isolate.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-embedder-heap.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-microtask.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-statistics.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-promise.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-unwinder.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-embedder-state-scope.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-platform.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-json.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-locker.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-microtask-queue.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-primitive-object.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-proxy.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-regexp.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-typed-array.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-value-serializer.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8-wasm.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node_version.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node_api.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/js_native_api.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/js_native_api_types.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node_api_types.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node_buffer.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/v8.h \
 ../src/cryptonote_core/cryptonote_basic.h \
 ../src/serialization/serialization.h ../src/serialization/string.h \
 ../src/serialization/vector.h ../src/serialization/variant.h \
 ../src/serialization/binary_archive.h ../src/common/varint.h \
 ../src/contrib/epee/include/warnings.h \
 ../src/serialization/json_archive.h ../src/serialization/debug_archive.h \
 ../src/serialization/crypto.h ../src/crypto/chacha8.h \
 ../src/crypto/hash.h ../src/common/pod-class.h \
 ../src/crypto/generic-ops.h ../src/crypto/hash-ops.h \
 ../src/crypto/crypto.h ../src/crypto/random.h \
 ../src/contrib/epee/include/serialization/keyvalue_serialization.h \
 ../src/contrib/epee/include/misc_log_ex.h \
 ../src/contrib/epee/include/static_initializer.h \
 ../src/contrib/epee/include/string_tools.h \
 ../src/contrib/epee/include/time_helper.h \
 ../src/contrib/epee/include/pragma_comp_defs.h \
 ../src/contrib/epee/include/misc_os_dependent.h \
 ../src/contrib/epee/include/syncobj.h \
 ../src/contrib/epee/include/serialization/enableable.h \
 ../src/contrib/epee/include/serialization/keyvalue_serialization_overloads.h \
 ../src/contrib/epee/include/string_tools.h ../src/cryptonote_config.h \
 ../src/contrib/epee/include/misc_language.h \
 ../src/cryptonote_core/tx_extra.h \
 ../src/cryptonote_core/cryptonote_format_utils.h \
 ../src/cryptonote_protocol/cryptonote_protocol_defs.h \
 ../src/cryptonote_protocol/blobdatatype.h \
 ../src/cryptonote_core/cryptonote_basic_impl.h \
 ../src/cryptonote_core/difficulty.h ../src/cryptonote_core/account.h \
 ../src/contrib/epee/include/include_base_utils.h \
 ../src/contrib/epee/include/misc_log_ex.h ../src/common/base58.h \
 ../src/serialization/binary_utils.h ../../nan/nan.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node_version.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/uv.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/uv/errno.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/uv/version.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/uv/unix.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/uv/threadpool.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/uv/linux.h \
 /home/less/.cache/node-gyp/18.20.4/include/node/node_object_wrap.h \
 ../../nan/nan_callbacks.h ../../nan/nan_callbacks_12_inl.h \
 ../../nan/nan_maybe_43_inl.h ../../nan/nan_converters.h \
 ../../nan/nan_converters_43_inl.h ../../nan/nan_new.h \
 ../../nan/nan_implementation_12_inl.h ../../nan/nan_persistent_12_inl.h \
 ../../nan/nan_weak.h ../../nan/nan_object_wrap.h ../../nan/nan_private.h \
 ../../nan/nan_typedarray_contents.h ../../nan/nan_json.h \
 ../../nan/nan_scriptorigin.h
../src/main.cc:
/home/less/.cache/node-gyp/18.20.4/include/node/node.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8.h:
/home/less/.cache/node-gyp/18.20.4/include/node/cppgc/common.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8config.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-array-buffer.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-local-handle.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-internal.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-version.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8config.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-object.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-maybe.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-persistent-handle.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-weak-callback-info.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-primitive.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-data.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-value.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-traced-handle.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-container.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-context.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-snapshot.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-date.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-debug.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-script.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-message.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-exception.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-extension.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-external.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-function.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-function-callback.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-template.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-memory-span.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-initialization.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-callbacks.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-isolate.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-embedder-heap.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-microtask.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-statistics.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-promise.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-unwinder.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-embedder-state-scope.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-platform.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-json.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-locker.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-microtask-queue.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-primitive-object.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-proxy.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-regexp.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-typed-array.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-value-serializer.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8-wasm.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node_version.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node_api.h:
/home/less/.cache/node-gyp/18.20.4/include/node/js_native_api.h:
/home/less/.cache/node-gyp/18.20.4/include/node/js_native_api_types.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node_api_types.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node_buffer.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node.h:
/home/less/.cache/node-gyp/18.20.4/include/node/v8.h:
../src/cryptonote_core/cryptonote_basic.h:
../src/serialization/serialization.h:
../src/serialization/string.h:
../src/serialization/vector.h:
../src/serialization/variant.h:
../src/serialization/binary_archive.h:
../src/common/varint.h:
../src/contrib/epee/include/warnings.h:
../src/serialization/json_archive.h:
../src/serialization/debug_archive.h:
../src/serialization/crypto.h:
../src/crypto/chacha8.h:
../src/crypto/hash.h:
../src/common/pod-class.h:
../src/crypto/generic-ops.h:
../src/crypto/hash-ops.h:
../src/crypto/crypto.h:
../src/crypto/random.h:
../src/contrib/epee/include/serialization/keyvalue_serialization.h:
../src/contrib/epee/include/misc_log_ex.h:
../src/contrib/epee/include/static_initializer.h:
../src/contrib/epee/include/string_tools.h:
../src/contrib/epee/include/time_helper.h:
../src/contrib/epee/include/pragma_comp_defs.h:
../src/contrib/epee/include/misc_os_dependent.h:
../src/contrib/epee/include/syncobj.h:
../src/contrib/epee/include/serialization/enableable.h:
../src/contrib/epee/include/serialization/keyvalue_serialization_overloads.h:
../src/contrib/epee/include/string_tools.h:
../src/cryptonote_config.h:
../src/contrib/epee/include/misc_language.h:
../src/cryptonote_core/tx_extra.h:
../src/cryptonote_core/cryptonote_format_utils.h:
../src/cryptonote_protocol/cryptonote_protocol_defs.h:
../src/cryptonote_protocol/blobdatatype.h:
../src/cryptonote_core/cryptonote_basic_impl.h:
../src/cryptonote_core/difficulty.h:
../src/cryptonote_core/account.h:
../src/contrib/epee/include/include_base_utils.h:
../src/contrib/epee/include/misc_log_ex.h:
../src/common/base58.h:
../src/serialization/binary_utils.h:
../../nan/nan.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node_version.h:
/home/less/.cache/node-gyp/18.20.4/include/node/uv.h:
/home/less/.cache/node-gyp/18.20.4/include/node/uv/errno.h:
/home/less/.cache/node-gyp/18.20.4/include/node/uv/version.h:
/home/less/.cache/node-gyp/18.20.4/include/node/uv/unix.h:
/home/less/.cache/node-gyp/18.20.4/include/node/uv/threadpool.h:
/home/less/.cache/node-gyp/18.20.4/include/node/uv/linux.h:
/home/less/.cache/node-gyp/18.20.4/include/node/node_object_wrap.h:
../../nan/nan_callbacks.h:
../../nan/nan_callbacks_12_inl.h:
../../nan/nan_maybe_43_inl.h:
../../nan/nan_converters.h:
../../nan/nan_converters_43_inl.h:
../../nan/nan_new.h:
../../nan/nan_implementation_12_inl.h:
../../nan/nan_persistent_12_inl.h:
../../nan/nan_weak.h:
../../nan/nan_object_wrap.h:
../../nan/nan_private.h:
../../nan/nan_typedarray_contents.h:
../../nan/nan_json.h:
../../nan/nan_scriptorigin.h:
