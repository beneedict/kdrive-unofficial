srpm:
	dnf -y install rpmdevtools
	spectool -g -R kdrive-unofficial.spec
	tar czf sentry-stub.tar.gz sentry-stub
	tar czf cmake-modules.tar.gz cmake-modules
	rpmbuild -bs --define "_sourcedir $(shell pwd)" --define "_srcrpmdir $(outdir)" kdrive-unofficial.spec
