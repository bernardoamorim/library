# a is the name of the tested code, a2 is brute force code and gen is the generator
# to run do: bash stress.sh 
# to create executable do: ch +x stress.sh

make a a2 gen || exit 1
for ((i = 1; ; i++)) do
	./gen $i > in
	./a < in > out
	./a2 < in > out2
	if (! cmp -s out out2) then
		echo "--> in:"
		cat in
		echo "--> out1:"
		cat out
		echo "--> out2:"
		cat out2
		break;
	fi
	echo $i
done
