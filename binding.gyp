{
    "targets": [
        {
            "target_name": "equihashverify",
            "dependencies": [
            ],
            "sources": [
                "src/blake/blake2-config.h",
                "src/blake/blake2-impl.h",
                "src/blake/blake2-round.h",
                "src/blake/blake2.h",
                "src/blake/blake2b-load-sse2.h",
                "src/blake/blake2b-load-sse41.h",
                "src/blake/blake2b-round.h",
                "src/blake/blake2b.cpp",
                "src/equi/equihash.cpp",
                "src/equi/endian.c",
                "equihashverify.cc",
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")",
            ],
            "defines": [
            ],
            "cflags_cc": [
                "-std=c++11",
                "-Wl,--whole-archive",
                "-fPIC",
                "-fexceptions",
            ],
            "link_settings": {
                "libraries": [
                    "-Wl,-rpath,./build/Release/",
                ]
            },
            "conditions": [
                ['OS=="mac"', {
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                    }
                }]
            ]
        }
    ]
}
