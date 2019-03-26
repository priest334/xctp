{
  'conditions': [
    ['OS=="win"', {
      'variables': {
        'sdkdir': '$(curl)',
      },
      'include_dirs': [
        '<(sdkdir)/include',
      ],
      'library_dirs': [
        '<(sdkdir)/lib',
      ],
      'link_settings': {
        'libraries': [
          #'-lAdvapi32',
          '-llibcurl',
        ]
      },
    }],# OS!="win"
    ['OS!="win"', {
      'link_settings': {
        'libraries': [
          '-lcurl',
        ],
      },
    }],
  ],
}