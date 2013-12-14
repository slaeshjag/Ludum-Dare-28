default:
	@mkdir -p res
	@echo " [LDMZ] testlevel.tmx"
	@darnit-tmxconv testlevel.tmx res/testlevel.ldmz 2>/dev/null
	@cp dummy.file res/
	@echo " [ LDI] res/"
	@darnit-fsimage res/ res.ldi
	@cat res.ldi >> ../bin/ld28.elf
	@rm res.ldi
	@ rm -Rf res/

clean:
