# Copyright 2019 the V8 project authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

vars = {
  'build_revision': '5b91f2d38785680d33c532ecb1a853a03f3ad6af',
  'build_url': 'https://chromium.googlesource.com/chromium/src/build.git',

  'buildtools_revision': '3e50219fc4503f461b2176a9976891b28d80f9ab',
  'buildtools_url': 'https://chromium.googlesource.com/chromium/src/buildtools.git',

  'clang_revision': '3dd606a4e91b32c6f0116b38abac3ab0c4944ec3',
  'clang_url': 'https://chromium.googlesource.com/chromium/src/tools/clang.git',

  'depot_tools_revision': 'efe902b20b6ae0d367b354bdaa2e10c19349f880',
  'depot_tools_url': 'https://chromium.googlesource.com/chromium/tools/depot_tools.git',

  # TODO(jgruber): Newer revisions (ae68779) are broken.
  'fuchsia_revision': '8e8db13b538ecb251e5ce9d5c781fc142f9752fd',
  'fuchsia_url': 'https://chromium.googlesource.com/chromium/src/third_party/fuchsia-sdk.git',

  'googletest_revision': '8b6d3f9c4a774bef3081195d422993323b6bb2e0',
  'googletest_url': 'https://chromium.googlesource.com/external/github.com/google/googletest.git',

  'icu_revision': '4ae7482a0e9e1f77a793545d803086a5ad4bcfd8',
  'icu_url': 'https://chromium.googlesource.com/chromium/deps/icu.git',

  'jinja2_revision': 'b41863e42637544c2941b574c7877d3e1f663e25',
  'jinja2_url': 'https://chromium.googlesource.com/chromium/src/third_party/jinja2.git',

  'markupsafe_revision': '8f45f5cfa0009d2a70589bcda0349b8cb2b72783',
  'markupsafe_url': 'https://chromium.googlesource.com/chromium/src/third_party/markupsafe.git',

  # TODO(jgruber): Upstream changes.
  'node_revision': 'for-upstream',
  'node_url': 'https://github.com/schuay/node.git',

  'trace_common_revision' : '936ba8a963284a6b3737cf2f0474a7131073abee',
  'trace_common_url': 'https://chromium.googlesource.com/chromium/src/base/trace_event/common.git',

  'v8_revision': '3a6ecfecba58718a4dc9457d24e839f8f22ccb47',
  'v8_url': 'https://chromium.googlesource.com/v8/v8.git',
}

deps = {
  'node-ci/base/trace_event/common': Var('trace_common_url') + '@' + Var('trace_common_revision'),
  'node-ci/build': Var('build_url') + '@' + Var('build_revision'),
  'node-ci/buildtools': Var('buildtools_url') + '@' + Var('buildtools_revision'),
  'node-ci/node': Var('node_url') + '@' + Var('node_revision'),
  'node-ci/third_party/depot_tools': Var('depot_tools_url') + '@' + Var('depot_tools_revision'),
  'node-ci/third_party/fuchsia-sdk': {
    'url': Var('fuchsia_url') + '@' + Var('fuchsia_revision'),
    'condition': 'checkout_fuchsia',
  },
  'node-ci/third_party/googletest/src': Var('googletest_url') + '@' + Var('googletest_revision'),
  'node-ci/third_party/icu': Var('icu_url') + '@' + Var('icu_revision'),
  'node-ci/third_party/jinja2': Var('jinja2_url') + '@' + Var('jinja2_revision'),
  'node-ci/third_party/markupsafe': Var('markupsafe_url') + '@' + Var('markupsafe_revision'),
  'node-ci/third_party/qemu-linux-x64': {
      'packages': [
          {
              'package': 'fuchsia/qemu/linux-amd64',
              'version': '9cc486c5b18a0be515c39a280ca9a309c54cf994'
          },
      ],
      'condition': 'host_os == "linux" and checkout_fuchsia',
      'dep_type': 'cipd',
  },
  'node-ci/tools/clang': Var('clang_url') + '@' + Var('clang_revision'),
  'node-ci/v8': Var('v8_url') + '@' +  Var('v8_revision'),
}

recursedeps = [
  'node-ci/buildtools',
]

hooks = [
  {
    'name': 'generate_node_filelist',
    'pattern': 'node-ci/node',
    'action': ['python', 'node-ci/tools/generate_node_files_json.py'],
  },
  {
    # Update the Windows toolchain if necessary.
    'name': 'win_toolchain',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['python', 'node-ci/build/vs_toolchain.py', 'update'],
  },
  {
    'name': 'clang',
    'pattern': '.',
    'action': ['python', 'node-ci/tools/clang/scripts/update.py'],
  },
  {
    'name': 'fuchsia_sdk',
    'pattern': '.',
    'condition': 'checkout_fuchsia',
    'action': [
      'python',
      'node-ci/build/fuchsia/update_sdk.py',
    ],
  },
  {
    # Update LASTCHANGE.
    'name': 'lastchange',
    'pattern': '.',
    'action': ['python', 'node-ci/build/util/lastchange.py',
               '-o', 'node-ci/build/util/LASTCHANGE'],
  },
  # Pull GN using checked-in hashes.
  {
    'name': 'gn_win',
    'pattern': '.',
    'condition': 'host_os == "win"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=win32',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'node-ci/buildtools/win/gn.exe.sha1',
    ],
  },
  {
    'name': 'gn_mac',
    'pattern': '.',
    'condition': 'host_os == "mac"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=darwin',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'node-ci/buildtools/mac/gn.sha1',
    ],
  },
  {
    'name': 'gn_linux',
    'pattern': '.',
    'condition': 'host_os == "linux"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--platform=linux*',
                '--no_auth',
                '--bucket', 'chromium-gn',
                '-s', 'node-ci/buildtools/linux64/gn.sha1',
    ],
  },
  {
    'name': 'sysroot_x64',
    'pattern': '.',
    'condition': 'checkout_linux and checkout_x64',
    'action': ['python',
               'node-ci/build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=x64'],
  },
]
