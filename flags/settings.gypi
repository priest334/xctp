{
  'conditions': [
    ['OS=="win"', {
      'defines': [
        'OS_WIN',
        'WIN32',
        '_WIN32_WINNT=0x501',
        '_MBCS',
      ],
      'msbuild_toolset': {
        #'PlatformToolset': 'v120',
      },
      'msvs_settings': {
        'VCCLCompilerTool': {
          'ExceptionHandling': '1',
        },
        'VCLinkerTool': {
          'GenerateDebugInformation': 'true',
          'LinkIncremental': '1',
          'LinkLibraryDependencies': 'true',
          'SubSystem': '1',
          'AdditionalDependencies': [
            '%(AdditionalDependencies)',
          ],
        },
      },
      'msvs_disabled_warnings': [
        '4503',
      ],
    }],# OS!="win"
    ['OS!="win"', {
      
    }],
  ],
}