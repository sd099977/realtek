.global start
.global end
.word	end - start
start:
.incbin "../../bin/image/hw_setting/backup.bin"
end:
