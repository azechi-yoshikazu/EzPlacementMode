<h1 align="center">
  <img src="https://github.com/azechi-yoshikazu/Images/blob/main/EzPlacementMode/logo.png" width="300"/>
  <p>
    EzPlacementMode
  </p>
</h1>
<p align="center">
  <strong>
    Place Actorsパネルへのカテゴリ追加を簡単に行えるようにするUnreal Engine 5向けのプラグイン
  </strong>
</p>
<div align="center">
  <a href="#license">
    <img alt="GitHub" src="https://img.shields.io/github/license/azechi-yoshikazu/EzPlacementMode?style=flat-square">
  </a>
  <a href="https://github.com/azechi-yoshikazu/EzPlacementMode/releases/latest">
    <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/azechi-yoshikazu/EzPlacementMode?style=flat-square">
  </a>
</div>
<p align="center">
  <a href="#introduction">Introduction</a> | 
  <a href="#supported-version">Supported Version</a> | 
  <a href="#how-to-use">How To Use</a> | 
  <a href="#download">Download</a> | 
  <a href="#license">License</a>
</p>
<p align="center">
  <img src="https://github.com/azechi-yoshikazu/Images/blob/main/EzPlacementMode/overview.gif" width="90%">
</p>

## Introduction
Unreal Engine 5向けのエディタ拡張プラグインです。

`Place Actors`パネルは通常、エディタ標準で用意されたカテゴリのみ表示されます。

通常はC++を使用しなければカテゴリを追加することはできませんが、本プラグインによりエディタからのカテゴリ追加を行うことができます。

## Supported Version
Unreal Engine 5.x

## How To Use
### カテゴリの追加方法
`Project Settings > Plugins > Ez Placement Mode`を開き、`Ez Placement Mode Settings`の`Categories`を追加してください。

### カテゴリ設定
- ***Name***
  - エディタ上で表示される、このカテゴリの名称です。
  - ※この項目が空の場合はエディタへの表示は行われません
- ***Priority***
  - カテゴリの優先度です。低い数値ほど優先度が高く、先に表示されるようになります。
  - 初期値の100を基準として大きい数値を使用するのがおすすめです。
- ***Actors***
  - カテゴリ内で表示したい`Actor`のリストです。
- ***Icon***
  - カテゴリのアイコンにするテクスチャです。
- ***IconColor***
  - カテゴリのアイコンカラーです。
  - `Icon`が指定されている場合のみ有効です。

## Download
リリースから[最新バージョン](https://github.com/azechi-yoshikazu/EzPlacementMode/releases/latest)をダウンロードすることができます。

## License
MIT
