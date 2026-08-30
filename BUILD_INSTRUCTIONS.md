# YM2203Synth VST3 Plugin - ビルド手順

## 前提条件
- Windows 10以上
- Visual Studio 2022
- JUCE 7.0以上（インストール済み）

## 手順

### 1. プロジェクトファイルの準備

```
C:\Users\[ユーザー名]\Documents\YM2203VST3\
├── Source/
│   ├── YM2203_Emulator/
│   │   ├── YM2203.h
│   │   └── YM2203.cpp
│   ├── VGZParser/
│   │   ├── VGZParser.h
│   │   └── VGZParser.cpp
│   ├── Plugin/
│   │   ├── PluginProcessor.h
│   │   ├── PluginProcessor.cpp
│   │   ├── PluginEditor.h
│   │   ├── PluginEditor.cpp
│   │   └── JucePluginDefines.h
│   └── PluginParams.h
├── YM2203Synth.jucer
├── CMakeLists.txt
└── setup.bat
```

### 2. Projucerプロジェクトを開く

1. **Projucer.exeを起動**
   ```
   C:\JUCE\extras\Projucer\Builds\VisualStudio2022\x64\Release\Projucer.exe
   ```

2. **Global Pathsを設定**
   - メニュー: `File` → `Global Paths...`
   - **JUCE Path**: `C:\JUCE`
   - **OK** をクリック

3. **YM2203Synth.jucerを開く**
   - メニュー: `File` → `Open...`
   - `C:\Users\[ユーザー名]\Documents\YM2203VST3\YM2203Synth.jucer` を選択

### 3. Visual Studioプロジェクトを生成

1. **Projucerで保存＆生成**
   - メニュー: `File` → `Save Project and Open in IDE`
   - Visual Studioが自動で起動します

### 4. ビルド

1. **Visual Studioでビルド**
   - メニュー: `ビルド` → `ソリューションのビルド`
   - または `Ctrl + Shift + B`
   - ビルドが完了するまで待機（数分かかります）

2. **ビルド成功の確認**
   - 出力ウィンドウに「ビルドが成功しました」と表示される

### 5. VST3プラグインの配置

ビルド後、生成されたVST3プラグイン（.dll）を以下にコピーします：

```
C:\Program Files\Common Files\VST3\YM2203Synth.vst3\
```

### 6. Cubaseでの使用

1. **Cubaseを再起動** （プラグインスキャンを実行）
2. **Cubaseでプラグインを追加**
   - インストルメント選択時に「YM2203Synth」が表示されます

## トラブルシューティング

### ビルドエラー: "Cannot find JUCE modules"
→ Projucerで Global Paths が正しく設定されているか確認

### プラグインが認識されない
→ VST3フォルダに正しく配置されているか確認
```
C:\Program Files\Common Files\VST3\
```

### Visual Studioが起動しない
→ 以下を確認:
- Visual Studio 2022が完全にインストールされているか
- Projucerのプロジェクトファイルが破損していないか（.jucerファイルを再度生成）

## サポート
- JUCE Documentation: https://docs.juce.com/
- VGM Format: https://www.smspower.org/