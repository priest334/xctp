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
  'copies': [
    {
      'destination': '<(PRODUCT_DIR)/third_party/ctp',
      'files': [
        'libthostmduserapi.so',
        'libthosttraderapi.so',
      ],
    }
  ]
}