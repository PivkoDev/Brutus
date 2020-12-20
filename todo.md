- Add .gitignore

- Tier class for binding Rules to Actions
- unit test - extract learn vector data from net


Additional include directories
..\ReMind\src\
D:\C\Externals\boost_1_64_0

Additional library directories
Release / Debug


Ważność	Kod	Opis	Projekt	Plik	Wiersz	Stan pominięcia
Błąd	LNK1104	nie można otworzyć pliku „libboost_serialization-vc141-mt-sgd-1_64.lib”	BrutusTests	D:\C\Projekty\Brutus\BrutusTests\LINK	1	


Boost's -mt-s corresponds to VS' Runtime Library setting /MT
Boost's -mt-sgd corresponds to VS' Runtime Library setting /MTd
Boost's -mt corresponds to VS' Runtime Library setting /MD
Boost's -mt-gd corresponds to VS' Runtime Library setting /MDd

b2 release debug threading=multi --build-type=complete --toolset=msvc address-model=64 stage

--toolset=vc141 "--toolset-root=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\ "  clean 
--toolset=vc141 "--toolset-root=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\ "  stage 

b2 -j8 toolset=msvc-14.1 address-model=64 architecture=x86

b2 -j8 toolset=vc141 toolset-root=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\ address-model=64 architecture=x86 stage

b2 -j8 --build-type=complete stage
Bledy:

\Microsoft was unexpected at this time
usuniecie "" z  PATH

