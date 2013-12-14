default:
	@mkdir -p res
	@cp dummy.file res/
	@echo " [ LDI] res/"
	@darnit-fsimage res/ res.ldi
	@cat res.ldi >> ../bin/ld28.elf
	@rm res.ldi

clean:
