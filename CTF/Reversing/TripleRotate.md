## TripleRotate-SecuInside2017

이번 문제는 시큐인사이드 2017 예선에 나온 리버싱문제입니다. 대회기간중에 문제를 풀지는 못했습니다. ㅠㅠ 리버싱전부 다 분석해서 암호화 알고리즘까지 전부 재현해냈는데 암호화된 키를 복호화시키는 방법을 생각못하고 손으로 무식하게 풀려다 망했어요. 이문제에 시간 거의 다투자해서 다른문제는 문제 읽지도 못했네요. ㅜㅜ 왜 1년반이나 공부해도 실력이 늘지 않을까요 ㅋㅋㅋ. 이 엄청난 무식함이란. 그럼 바로 시작해보도록 하겠습니다. 

먼저 리버싱을 통해서 원래의 c 코드로 복구하는 작업을 먼저 해보도록 하겠습니다. `0040076d         cmp        rax, 0x9` 먼저 여기서 input의 길이를 검사합니다 `rax`안에는 input의 길이가 들어있습니다. 따라서 입력이 9가 아니라면 프로그램이 실행되지 않습니다. 여기서 flag의 길이가 9일것일거라고 생각할 수 있습니다. 
<pre><code>
0000000000400799         lea        rdx, qword [rbp+var_2C]
000000000040079d         mov        rsi, rdx
00000000004007a0         mov        rdi, rax
00000000004007a3         mov        eax, 0x0
00000000004007a8         call       j___isoc99_scanf
00000000004007ad         mov        eax, dword [rbp+var_2C]
00000000004007b0         cmp        eax, 0xc8
00000000004007b5         ja         loc_4007c6
00000000004007b7         mov        edi, 0x400ce6                               ; "check your length", argument "s" for method j_puts
00000000004007bc         call       j_puts
00000000004007c1         jmp        loc_400860
                     loc_4007c6:
00000000004007c6         mov        eax, dword [rbp+var_2C]                     ; CODE XREF=sub_400704+177
00000000004007c9         mov        eax, eax
00000000004007cb         mov        rdi, rax                                    ; argument "size" for method j_malloc
00000000004007ce         call       j_malloc
00000000004007d3         mov        qword [rbp+var_40], rax
00000000004007d7         mov        eax, dword [rbp+var_2C]
00000000004007da         mov        ecx, eax
00000000004007dc         mov        rdx, qword [rbp+var_40]                     ; argument #3 for method sub_400876
00000000004007e0         lea        rax, qword [rbp+var_20]
00000000004007e4         mov        esi, ecx                                    ; argument #2 for method sub_400876
00000000004007e6         mov        rdi, rax                                    ; argument #1 for method sub_400876
00000000004007e9         call       sub_400876
00000000004007ee         mov        edx, 0x400cf8
00000000004007f3         mov        eax, 0x400cfb                               ; "encrypt"
00000000004007f8         mov        rsi, rdx                                    ; argument "mode" for method j_fopen
00000000004007fb         mov        rdi, rax                                    ; argument "filename" for method j_fopen
00000000004007fe         call       j_fopen
0000000000400803         mov        qword [rbp+var_38], rax
0000000000400807         mov        dword [rbp+var_28], 0x0
000000000040080e         jmp        loc_400856
                     loc_400810:
0000000000400810         mov        eax, dword [rbp+var_28]                     ; CODE XREF=sub_400704+346
0000000000400813         cdqe
0000000000400815         add        rax, qword [rbp+var_40]
0000000000400819         movzx      eax, byte [rax]
000000000040081c         test       al, al
000000000040081e         je         loc_400827
0000000000400820         mov        eax, 0x31
0000000000400825         jmp        loc_40082c
                     loc_400827:
0000000000400827         mov        eax, 0x30                                   ; CODE XREF=sub_400704+282
                     loc_40082c:
000000000040082c         mov        byte [rbp+var_21], al                       ; CODE XREF=sub_400704+289
000000000040082f         movsx      eax, byte [rbp+var_21]
0000000000400833         mov        rdx, qword [rbp+var_38]
0000000000400837         mov        rsi, rdx                                    ; argument "stream" for method j_fputc
000000000040083a         mov        edi, eax                                    ; argument "c" for method j_fputc
000000000040083c         call       j_fputc
0000000000400841         mov        rax, qword [rbp+var_38]
0000000000400845         mov        rsi, rax                                    ; argument "stream" for method j_fputc
0000000000400848         mov        edi, 0x20                                   ; argument "c" for method j_fputc
000000000040084d         call       j_fputc
0000000000400852         add        dword [rbp+var_28], 0x1
                     loc_400856:
0000000000400856         mov        edx, dword [rbp+var_28]                     ; CODE XREF=sub_400704+266
0000000000400859         mov        eax, dword [rbp+var_2C]
000000000040085c         cmp        edx, eax
000000000040085e         jb         loc_400810
</code></pre>
여기서 아래 2개의 명령어를 봅시다. 
<pre><code>
0000000000400799         lea        rdx, qword [rbp+var_2C]
000000000040079d         mov        rsi, rdx
00000000004007a0         mov        rdi, rax
00000000004007a3         mov        eax, 0x0
00000000004007a8         call       j___isoc99_scanf
</code></pre>
</br>
<pre><code>
0000000000400856         mov        edx, dword [rbp+var_28]                     ; CODE XREF=sub_400704+266
0000000000400859         mov        eax, dword [rbp+var_2C]
000000000040085c         cmp        edx, eax
000000000040085e         jb         loc_400810
</pre></code>
저 2개의 명령어를 보면 2번째 입력의 의미를 알 수 있습니다. 2번째 입력은 `rbp+var_2C`에 저장되고 `main`함수의 거의 마지막 부분에서 `rbp+var_28`의 값을 0으로 초기화하고 반복문을 돌때마다 1씩 값을 늘려가며아까 입력한 값과 비교하는 것을 알수 있습니다. 즉 입력한 값만큼 반복문을 돌게 되는것인데 반복문 1번을 돌때마다 2Byte 씩 값을 쓰게 되므로 암호화 파일인 402 바이트의 절반, 즉 201을 입력하면 됩니다.

이제 `main`함수에서 호출하는 `sub_400876`를 보도록 하겠습니다. 이 함수는 크게 3부분으로 나누어 볼수 있는데 첫번째 부분(`00000000004008ab~00000000004008cd`)은 ASCII코드를 2진수로 바꿔주는 역할을 합니다. 만약 `abcd...`와 같이 입력했다면 `011000010110001001100011001100100...`로 변환해주는 역할을 합니다. 2번째 부분은 `sub_400876`를 호출합니다. 저 함수는 1번째 부분에서 만들어준 2진수 72개의 바이트를 순서를 막섞는 역할을 해줍니다. 먼저 72개의 바이트를 8개씩 9개로 나눕니다. 그리고 각각의 묶음내에 비트를 역순으로 바꿔줍니다. 그리고 다시 72개의 1개 배열로 합칩니다. 그리고 그배열을 각각 `0x17`, `0x18`, `0x19`씩 나누어 넣습니다. 그다음은 세개의 배열을 모두 201의 크기가 되도록 xor시켜줍니다. a[i]^a[i+5]를 배열의 가장 마지막에 추가해줍니다. 그렇게 201의 크기가 될때까지 반복해줍니다. 드디어 3번째 부분을 생각해보도록 하겠습니다. 3번째 부분은 2번째 부분에서 나뉘었던 3개의 배열을 1개로 합쳐주는 역할을 합니다. 3개의 배열을 a, b, c라고 부르고 결과물 배열을 r이라고 부르겠습니다. 그렇게 해서 r[i] = c[i]^(a[i]&b[i])^(b[i]&c[i]) 이라는 알고리즘을 이용해서 암호화하면 됩니다. 그렇게되면 r의 크기가 201이 되고 그게 통째로 파일에 들어갑니다. 이제 그걸 python으로 짜보도록 하겠습니다.

<pre><code>
in1 = raw_input('First_input')
if len(in1) != 9:
    exit(0)
in2 = raw_input('Second_input')
conversion = ''
res = ''
for char in in1:
    tmp = bin(ord(char))[2:]
    tmp = '0'*(8-len(tmp))+tmp
    conversion += tmp[::-1]
array1 = conversion[:0x17]
array2 = conversion[0x17:0x17+0x18]
array3 = conversion[0x17+0x18:]
array1 = map(int, list(array1))
array2 = map(int, list(array2))
array3 = map(int, list(array3))
for idx in range(0, int(in1) - 0x17):
    array1.append(array1[idx + 5] ^ array1[idx])
for idx in range(0, int(in1) - 0x18):
    array2.append(array2[idx + 1] ^array2[idx + 2] ^ array2[idx + 4] ^ array2[idx])
for idx in range(0, int(in1) - 0x19):
    array3.append(array3[idx + 3] ^ array3[idx])
for idx in range(int(in1)):
    res += str(((array1[idx]&array2[idx])^(array2[idx]&array3[idx]))^array3[idx])+' '
with open('encryption', 'wt') as f:
    f.write(res)
</code></pre>

아마 이렇게 코드를 짤 수 있을것입니다. 여기까지는 대회중 분석을 마쳤는데 문제는 이 알고리즘을 통해서 복화하하는 과정을 도저히 생각하지 못했던 것입니다. 손으로도 해보고 `angr`모듈을 써보기도 했는데 2가지 경우모두 실패했습니다. 그래서 대회를 포기하고 말았는데 오늘나온 writeup을 보니까 `z3`이라는 모듈을 쓰더군요. `angr`모듈과 굉장히 비슷하다고 생각하는데 왜 angr로는 풀지 못했는지 아직도 이해가 되지 않습니다. 어쨌던 해당 암호문을 복호화시키는 스크립트는 아래와 같습니다.

<pre><code>
from z3 import *
length = 201
s = Solver()
arr_encrypted = "0 0 1 0 0 0 1 0 1 1 0 1 0 1 1 0 1 1 1 0 0 0 1 0 1 0 1 1 1 0 1 0 0 0 0 1 0 0 0 1 1 0 1 1 0 1 1 0 0 0 0 0 1 1 0 1 1 1 0 0 1 0 1 0 1 0 1 1 0 0 1 0 1 0 1 0 1 0 0 0 0 1 1 1 0 1 0 0 1 1 0 0 0 0 0 1 1 1 0 1 1 0 0 0 1 1 1 1 1 1 1 1 0 1 1 1 0 1 0 1 1 0 1 0 1 0 0 1 0 0 0 1 0 0 0 1 1 0 0 1 0 1 0 0 1 0 0 1 1 0 0 0 1 1 0 1 1 1 0 0 1 0 0 1 0 1 1 0 0 1 1 0 1 1 1 1 0 1 1 1 0 1 0 1 1 0 0 1 0 0 1 0 0 0 1 0 1 0 0 0 1".split(" ")
arr0 = [] # Output array
arr1 = [] # The three arrays used in the program...
arr2 = []
arr3 = []
for i in range(202):
	arr0.append(BitVec("arr0_%i" % i, 8))
	arr1.append(BitVec("arr1_%i" % i, 8))
	arr2.append(BitVec("arr2_%i" % i, 8))
	arr3.append(BitVec("arr3_%i" % i, 8))
i = 0
for str_bit in arr_encrypted:
	arr0[i] = ord(str_bit) - 0x30 # Make it either 0x00 or 0x01...
	i += 1
print("Adding conditions...")
# Conditions from fcn.00400acf
i = 0
while(length - 0x17 > i):
	s.add(arr1[i + 0x17] == arr1[i] ^ arr1[i + 5])
	i += 1
# Conditions from fcn.00400b22
i = 0
while(length - 0x18 > i):
	s.add(arr2[i + 0x18] == arr2[i] ^ (arr2[i + 1] ^ (arr2[i + 3] ^ arr2[i + 4])))
	i += 1
# Conditions from fcn.00400b9b
i = 0
while(length - 0x19 > i):
	s.add(arr3[i + 0x19] == arr3[i] ^ arr3[i + 3])
	i += 1
for i in range(202):
	# The merge that happens in malloc_876, maps the 3 arrays to the output (encrypt file)
	s.add(arr0[i] == ((arr1[i] & arr2[i]) ^ (arr2[i] & arr3[i])) ^ arr3[i])
	# Each number is either 0 or 1
	s.add(arr0[i] < 2)
	s.add(arr0[i] >= 0)
	s.add(arr1[i] < 2)
	s.add(arr1[i] >= 0)
	s.add(arr2[i] < 2)
	s.add(arr2[i] >= 0)
	s.add(arr3[i] < 2)
	s.add(arr3[i] >= 0)
print("Checking if solvable...")
print("Printing model..."),
print(s.check())
m = s.model()
print("Bitstring...")
res = ''
# Print first 0x17 bits of input string
for i in range(0x17):
	res += str(m[arr1[0x16 - i]])
# Print second 0x18 bits of input string
for i in range(0x18):
	res += str(m[arr2[0x17 - i]])
# Print final 0x19 bits of input string
for i in range(0x19):
	res += str(m[arr3[0x18 - i]])
flag = ''
for i in range(0, 72, 8):
    flag += chr(int(res[i:i+8], 2))
print 'SECU[%s]' %flag
</code></pre>

그리고 angr을 이용한 풀이에도 다시 도전해봐야겠네요. 혹시 모르는 부분이나 틀린부분이 있다면 메일로 알려주세요
