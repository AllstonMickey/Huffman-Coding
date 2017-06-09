#!/bin/csh
touch increment
foreach i (`seq 100`)
./increment -n 1000 > noMutex.txt
./increment -n 1000 -m > yesMutex.txt
diff noMutex.txt yesMutex.txt
echo '\n'
end
rm noMutex.txt yesMutex.txt
