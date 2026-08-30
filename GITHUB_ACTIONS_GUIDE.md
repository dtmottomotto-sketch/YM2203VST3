# GitHub Actions Auto-Build ガイド

## ビルドステータス確認

### Step 1: リポジトリの Actions タブを開く
1. https://github.com/dtmottomotto-sketch/YM2203VST3 にアクセス
2. **Actions** タブをクリック

### Step 2: ビルドの進行状況を確認
- 緑のチェックマーク ✅ = ビルド成功
- 赤の×マーク ❌ = ビルド失敗
- 黄色の円 ⏳ = ビルド中

---

## VST3プラグインのダウンロード

### 方法1: Artifacts からダウンロード（ビルド成功後）

1. ビルド完了後、Actions ページから最新のワークフロー実行を開く
2. **Artifacts** セクションまでスクロール
3. **YM2203Synth-Latest-Build** をクリックしてダウンロード
   - ZIPファイルに YM2203Synth.vst3 が含まれています

### 方法2: Release からダウンロード（タグ作成時）

1. タグを作成してプッシュすると自動で Release が作成されます
   ```bash
   git tag v1.0.0
   git push origin v1.0.0
   ```
2. GitHub リポジトリの **Releases** ページから YM2203Synth.vst3 をダウンロード

---

## VST3プラグインのインストール

### ダウンロード後の配置

```
C:\Program Files\Common Files\VST3\
    ↓
YM2203Synth.vst3\ ← ここにコピー
```

**手順：**
1. ダウンロードした `YM2203Synth.vst3` フォルダをコピー
2. `C:\Program Files\Common Files\VST3\` に貼り付け
3. Cubase を再起動
4. インストルメント選択時に「YM2203Synth」が表示されます

---

## ビルドが失敗した場合

### ステップ1: ログを確認
1. Actions ページでビルドをクリック
2. 失敗したステップの詳細ログを確認

### よくあるエラー

**Error: JUCE not found**
→ ネットワーク接続を確認（GitHub Actions から git clone が実行されます）

**Error: VST3 plugin not found**
→ ビルド手順を確認、MSBuild のパス設定を再確認

### サポート
- Issue を作成して報告してください
- https://github.com/dtmottomotto-sketch/YM2203VST3/issues

---

## ビルドのトリガー

ビルドは以下の場合に自動実行されます：

1. **Push** → main ブランチへのプッシュ
2. **Pull Request** → main ブランチへの PR
3. **Manual** → Actions ページで手動トリガー

---

## 手動ビルドのトリガー

1. https://github.com/dtmottomotto-sketch/YM2203VST3 の **Actions** タブ
2. 左メニューから **Build VST3 Plugin** をクリック
3. **Run workflow** をクリック
4. **Green Run workflow** ボタンをクリック

---

## トラブルシューティング

### Q: ビルドが完了しない
**A:** 
- GitHub Actions の実行キューをチェック
- 同時実行ジョブ数制限の可能性
- 数分待ってから再度確認

### Q: VST3 が認識されない
**A:**
- パスが正確か確認: `C:\Program Files\Common Files\VST3\`
- Cubase を完全に終了してから再起動
- Windows を再起動

### Q: プラグインが読み込まれない
**A:**
- VST3 のアーキテクチャ（x64）が Cubase と一致しているか確認
- Cubase のプラグインスキャンをリセット

---

## 次のステップ

✅ GitHub Actions でビルド実行
↓
✅ VST3 プラグイン (.vst3) をダウンロード
↓
✅ `C:\Program Files\Common Files\VST3\` に配置
↓
✅ Cubase で使用開始

🎹 完成！