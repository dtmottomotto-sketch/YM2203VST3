# YM2203Synth - VST3 Plugin

YM2203 FM音源エミュレーターのVST3プラグインです。
Furnaceで使用されているYM2203エミュレーターをベースにしており、PC-8801mk2SR相当の音源エンジンを搭載しています。

## 機能

- YM2203 FM音源のエミュレーション
- .vgzファイル（VGM Zip形式）の読み込みと再生
- リアルタイムパラメーター編集
- シンプルで直感的なUI
- Windows VST3プラグイン

## システム要件

- Windows 10以上
- Cubase 11以上（VST3対応版）
- Visual Studio 2022（開発用）
- JUCE 7.0以上

## セットアップ

### 開発環境の構築

1. JUCEをインストール
   ```
   https://juce.com/download/
   C:\JUCE に展開
   ```

2. Projucerでプロジェクトを開く
   ```
   YM2203Synth.jucer を Projucer で開く
   ```

3. Visual Studioプロジェクトを生成
   ```
   Projucer: File → Save Project and Open in IDE
   ```

4. Visual Studioでビルド
   ```
   ビルド → ソリューションのビルド
   出力: VST3プラグイン (.dll)
   ```

## VST3プラグインの配置

ビルド後、生成されたVST3プラグイン(.dll)を以下にコピー：
```
C:\Program Files\Common Files\VST3\
```

その後、Cubaseを再起動して使用できます。

## ライセンス

GPL-2.0 License
このプロジェクトはFurnaceのコードを使用しており、GPL-2.0ライセンスの下で公開されています。

## 参考資料

- Furnace: https://github.com/tildearrow/furnace
- VGM Format: https://www.smspower.org/
- JUCE Documentation: https://docs.juce.com/