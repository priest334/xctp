# Copyright (c) 2011 The TQ Authors. All rights reserved
# set GYP_GENERATORS=ninja,msvs-ninja
# set GYP_MSVS_VERSION=2017

{
  'targets': [
    {
      'target_name': 'all',
      'type': 'none',
      'msvs_guid': '072CC801-DC45-4D05-A359-8044E60DA334',
      'includes': [
      ],
      'dependencies': [
        'xctp/xctp.gyp:*',
      ],
    },
  ],
}
