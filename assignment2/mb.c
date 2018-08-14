#include <stdio.h>

int main (int argc, char *argv[])
  

  {
	
	/*
main():
 6b0:	55                   	push   %rbp
 6b1:	48 89 e5             	mov    %rsp,%rbp
 6b4:	48 83 ec 20          	sub    $0x20,%rsp
 6b8:	89 7d ec             	mov    %edi,-0x14(%rbp)
 6bb:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
 6bf:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
 6c6:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
 6cd:	eb 1b                	jmp    6ea <main+0x3a>
 6cf:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
 6d6:	eb 08                	jmp    6e0 <main+0x30>
 6d8:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
 6dc:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
 6e0:	83 7d f4 04          	cmpl   $0x4,-0xc(%rbp)
 6e4:	7e f2                	jle    6d8 <main+0x28>
 6e6:	83 45 f8 01          	addl   $0x1,-0x8(%rbp)
 6ea:	81 7d f8 3f 42 0f 00 	cmpl   $0xf423f,-0x8(%rbp)
 6f1:	7e dc                	jle    6cf <main+0x1f>
 6f3:	8b 45 fc             	mov    -0x4(%rbp),%eax
 6f6:	89 c6                	mov    %eax,%esi
 6f8:	48 8d 3d 95 00 00 00 	lea    0x95(%rip),%rdi        # 794 <_IO_stdin_used+0x4>
 6ff:	b8 00 00 00 00       	mov    $0x0,%eax
 704:	e8 57 fe ff ff       	callq  560 <printf@plt>
 709:	b8 00 00 00 00       	mov    $0x0,%eax
 70e:	c9                   	leaveq 
 70f:	c3                   	retq   */
//for every iteration 6 branches on 6e4 and 1 on 6f1	
	int a=0;
	for(int i=0;i<1000000;i++)
		for(int j=0; j<5; j++)
			a=a+1;
	


	printf("% d ",a);
return 0;

  }
