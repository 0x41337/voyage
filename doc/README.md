---
description: Voyage library Introduction
---

# ✈ Introduction

Voyage is a hook library for Unix-like systems. As mentioned in the README in main. If you have already worked with the Libmem, Dobby or Minhook libraries you will feel comfortable.

First you need to understand how to Voyage with hooks.&#x20;

Voyage uses a technique called <mark style="color:green;">detour</mark> which consists of injecting a `JMP` instruction for jump to another place in the program at run time.&#x20;

Therefore:

{% code lineNumbers="true" %}
```armasm
; Before the hook
; Add function
push ebp
mov ebp, esp
mov eax, [ebp + 8]
add eax, [ebp + 12]
pop ebp
ret

; After the hook
; Add function -> Hook function
jmp hook_address
```
{% endcode %}

If you still have doubts about how it works, you can watch the video below explaining it in detail.

{% embed url="https://www.youtube.com/watch?ab_channel=Zer0Mem0ry&v=b1ahj347pDc" %}
How function hooking / Detouring  works - By **ZeroMemory**
{% endembed %}
