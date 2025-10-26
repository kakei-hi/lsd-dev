# if-else サンプル（class_if_else）

このフォルダには if-else の使い方を示すサンプルコードが含まれているでござる。

ファイル一覧でござる:
- `if_else_sample.c` : if-else の例（実行可能な main を含む）でござる。

ルートのテストファイルでござる:
- `tests/if_else_test.c` : 小さな自動テストでござる。

コンパイルと実行（macOS zsh, clang）でござる:

```
# class_if_else の単体実行
clang -Wall -Wextra class_if_else/if_else_sample.c -o class_if_else/if_else_sample
./class_if_else/if_else_sample

# テスト実行（サンプルとテストを一緒にコンパイル）
clang -Wall -Wextra class_if_else/if_else_sample.c tests/if_else_test.c -o tests/if_else_test
./tests/if_else_test
```

説明:
- `is_even` : if-else の基本（偶数/奇数）でござる。
- `grade_comment` : if - else if - else の例で点数を評価するでござる。
- `demonstrate_nested` : ネストした if の例でござる。

学習目的のためコメントを多く記載しているでござる。自由に編集して試してほしいでござる。
