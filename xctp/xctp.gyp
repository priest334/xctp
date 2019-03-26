{
  'target_defaults': {
    'includes': [
      '../flags/configs.gypi',
      '../flags/settings.gypi',
      '../third_party/ctp/ctp.gypi',
      '../third_party/rapidjson/rapidjson.gypi',
      '../third_party/boost/boost.gypi',
    ],
    'include_dirs': [
      '..',
    ],
    'dependencies': [
    ],
  },
  'targets': [
    {
      'target_name': 'xtcp',
      'type': 'executable',
      'msvs_guid': 'F2D44926-89EC-49B3-BF10-E606EC4420FA',
      'dependencies': [
      ],
      'link_settings': {
        'libraries': [
        ],
      },
      'conditions': [
        ['OS == "win"', {
          'link_settings': {
            'libraries': [
              '-lws2_32',
            ]
          }
        }],
        ['OS != "win"', {
        }],
      ],
      'sources': [
        'ctp_session.cpp',
        'ctp_session.h',
        'io_context_pool.cpp',
        'io_context_pool.h',
        'json_wrapper.cpp',
        'json_wrapper.h',
        'md/mapper.h',
        'md/md_connector.cpp',
        'md/md_connector.h',
        'md/md_history.cpp',
        'md/md_history.h',
        'md/md_spi_handler.cpp',
        'md/md_spi_handler.h',
        'md/str_helper.h',
        'md/user_api_struct_mapper.h',
        'md_user_session_manager.cpp',
        'md_user_session_manager.h',
        'settings.cpp',
        'settings.h',
        'switch_wrapper.h',
        'websocket_server.cpp',
        'websocket_server.h',
        'websocket_session.cpp',
        'websocket_session.h',
        'ws_session_manager.cpp',
        'ws_session_manager.h',
        'xctp.cpp',
      ],
    },
  ],
}