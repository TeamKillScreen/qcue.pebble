./waf build

if [ $? -eq 0 ]
then
	cp ./build/app.pbw ~/Dropbox/qcue.pbw
	# ../libpebble/p.py --pebble_id 00:17:EC:D6:4B:01 --lightblue reinstall build/qcue.pbw
fi

