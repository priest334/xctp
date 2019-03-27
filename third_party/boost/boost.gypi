{
  'conditions': [
    ['OS=="win"', {
      'variables': {
        'sdkdir': '$(boost)',
      },
      'include_dirs': [
        '<(sdkdir)',
      ],
      'library_dirs': [
        '<(sdkdir)/stage/lib',
      ],
      'link_settings': {
        'libraries': [
          #'-lAdvapi32',
        ]
      },
    }],# OS!="win"
    ['OS!="win"', {
      'link_settings': {
        'libraries': [
          #'-lboost',
          '-pthread',
          '-lboost_chrono',
          '-lboost_context',
          '-lboost_progam_options',
          '-lboost_thread',
          '-lboost_timer',
        ],
      },
    }],
  ],
}