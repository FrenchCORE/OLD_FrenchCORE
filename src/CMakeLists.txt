# Copyright (C) 2005 - 2012 MaNGOS <http://www.getmangos.com/>
#
# Copyright (C) 2008 - 2012 Trinity <http://www.trinitycore.org/>
#
# Copyright (C) 2012 - 2012 FrenchCORE <http://www.frcore.com/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

add_subdirectory(genrev)
add_subdirectory(server)

if(TOOLS)
  add_subdirectory(tools)
endif(TOOLS)

