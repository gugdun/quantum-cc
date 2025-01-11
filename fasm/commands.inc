REG.R1?  equ [:0000b:]
REG.R2?  equ [:0001b:]
REG.R3?  equ [:0010b:]
REG.R4?  equ [:0011b:]
REG.R5?  equ [:0100b:]
REG.R6?  equ [:0101b:]
REG.R7?  equ [:0110b:]
REG.R8?  equ [:0111b:]
REG.R9?  equ [:1000b:]
REG.R10? equ [:1001b:]
REG.R11? equ [:1010b:]
REG.R12? equ [:1011b:]
REG.SP?  equ [:1100b:]
REG.PT?  equ [:1101b:]
REG.CR?  equ [:1110b:]
REG.PC?  equ [:1111b:]

macro NOP?
      db 00h
end macro

macro ADD? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 10h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro ADDS? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 11h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro SUB? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 12h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro SUBS? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 13h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro MUL? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 14h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro MULS? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 15h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro DIV? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 16h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro DIVS? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 17h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro MOD? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 18h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro INV? arg
      match [:r:], REG.arg
            db 19h
            db r1 shl 4
      end match
end macro

macro SHL? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 1Ah
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro SHR? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 1Bh
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro NOT? arg
      match [:r:], REG.arg
            db 1Ch
            db r shl 4
      end match
end macro

macro AND? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 1Dh
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro OR? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 1Eh
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro XOR? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 1Fh
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro JMP? arg
      db 20h
      dw arg
end macro

macro JL? arg1, arg2, arg3
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 21h
                  db r1 shl 4 + r2
                  dw arg3
            end match
      end match
end macro

macro JLE? arg1, arg2, arg3
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 22h
                  db r1 shl 4 + r2
                  dw arg3
            end match
      end match
end macro

macro JE? arg1, arg2, arg3
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 23h
                  db r1 shl 4 + r2
                  dw arg3
            end match
      end match
end macro

macro JNE? arg1, arg2, arg3
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 24h
                  db r1 shl 4 + r2
                  dw arg3
            end match
      end match
end macro


macro JGE? arg1, arg2, arg3
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 25h
                  db r1 shl 4 + r2
                  dw arg3
            end match
      end match
end macro

macro JG? arg1, arg2, arg3
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 26h
                  db r1 shl 4 + r2
                  dw arg3
            end match
      end match
end macro

macro LDB? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 31h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro LDBA? arg1, arg2
      match [:r1:], REG.arg1
            db 40h + r1
            dw arg2
      end match
end macro

macro LDBI? arg1, arg2
      match [:r1:], REG.arg1
            db 60h + r1
            db arg2
      end match
end macro

macro LDW? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 32h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro LDWA? arg1, arg2
      match [:r1:], REG.arg1
            db 50h + r1
            dw a
      end match
end macro

macro LDWI? arg1, arg2
      match [:r1:], REG.arg1
            db 70h + r1
            dw arg2
      end match
end macro

macro STB? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 33h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro STBA? arg1, arg2
      match [:r1:], REG.arg1
            db 80h
            dw arg2
      end match
end macro

macro STW? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 34h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro STWA? arg1, arg2
      match [:r1:], REG.arg1
            db 90h
            dw arg2
      end match
end macro

macro PUSH? arg
      match [:r:], REG.arg
            db 0A0h + r
      end match
end macro

macro POP? arg
      match [:r:], REG.arg
            db 0B0h + r
      end match
end macro

macro CALL? arg
      match [:r:], REG.arg
            db 0C0h + r
      else
            db 03Fh
            dw arg
      end match
end macro

macro RET?
      db 35h
end macro

macro MOV? arg1, arg2
      match [:r1:], REG.arg1
            match [:r2:], REG.arg2
                  db 36h
                  db r1 shl 4 + r2
            end match
      end match
end macro

macro INT? arg
      db 37h
      db arg
end macro

macro INC? arg
      match [:r:], REG.arg
            db 0D0h + r
      end match
end macro

macro DEC? arg
      match [:r:], REG.arg
            db 0E0h + r
      end match
end macro

macro HLT?
      db 0FFh
end macro
