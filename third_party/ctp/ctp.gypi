{
  'include_dirs': [
    '.',
  ],
  'library_dirs': [
    '.',
  ],
  'link_settings': {
    'libraries': [
      #'-lAdvapi32',
      '-lthostmduserapi',
    ]
  },
  'conditions':[
    ['OS=="win"',{
      'copies': [
        {
          'destination': '<(PRODUCT_DIR)',
          'files': [
            'thostmduserapi.dll',
            'thosttraderapi.dll',
          ],
        }
      ]
    }],
    ['OS!="win"',{
      'variables': {
        'shared_lib_dir': '<(PRODUCT_DIR)/third_party/ctp',
      },
      'ldflags': [
        '-Wl,-rpath=./third_party/ctp'
      ],
      'copies': [
        {
          'destination': '<(shared_lib_dir)',
          'files': [
            'libthostmduserapi.so',
            'libthosttraderapi.so',
          ],
        }
      ]
    }],
  ],
}