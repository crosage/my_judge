https://blog.csdn.net/A951860555/article/details/116738676


very usefully

__int64 sandbox()
{
  __int64 v1; // [rsp+8h] [rbp-8h]
  
  // 两个重要的宏，SCMP_ACT_ALLOW(0x7fff0000U) SCMP_ACT_KILL( 0x00000000U)
  // seccomp初始化，参数为0表示白名单模式，参数为0x7fff0000U则为黑名单模式
  v1 = seccomp_init(0LL);
  if ( !v1 )
  {
    puts("seccomp error");
    exit(0);
  }
  
  // seccomp_rule_add添加规则
  // v1对应上面初始化的返回值
  // 0x7fff0000即对应宏SCMP_ACT_ALLOW
  // 第三个参数代表对应的系统调用号，0-->read/1-->write/2-->open/60-->exit
  // 第四个参数表示是否需要对对应系统调用的参数做出限制以及指示做出限制的个数，传0不做任何限制
  seccomp_rule_add(v1, 0x7FFF0000LL, 2LL, 0LL);
  seccomp_rule_add(v1, 0x7FFF0000LL, 0LL, 0LL);
  seccomp_rule_add(v1, 0x7FFF0000LL, 1LL, 0LL);
  seccomp_rule_add(v1, 0x7FFF0000LL, 60LL, 0LL);
  seccomp_rule_add(v1, 0x7FFF0000LL, 231LL, 0LL);

  // seccomp_load - Load the current seccomp filter into the kernel
  if ( seccomp_load(v1) < 0 )
  {
  	// seccomp_release - Release the seccomp filter state
  	// 但对已经load的过滤规则不影响
    seccomp_release(v1);
    puts("seccomp error");
    exit(0);
  }
  return seccomp_release(v1);
}
