谁家好人手搓二进制B-Tree啊。  
把m1zole的ramdisk通过修改btree增加了一层，变为/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/disk.dmg，但好像没用，触发递归后还是不执行code；   
鉴于iPhone 4的特殊性，我们没有办法直接通过ramdiskF的恢复模式判断exploit成功与否；    
但我们可以通过m1zole的ramdisk与iloader来对iPhone 4s 7.0.4进行实机测试，鉴于两者的启动目录完全一致（seq均为22）。   
测试结果：直接通过修改u层为v层不可行，解析时依旧为按u层解析；应该直接生成一个合适的v层ramdisk；但问题来了：怎么生成这个ramdisk本身而不是什么ramdisk3、ramdiskF？谁能告诉我……
