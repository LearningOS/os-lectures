---

excalidraw-plugin: parsed

---
==⚠  Switch to EXCALIDRAW VIEW in the MORE OPTIONS menu of this document. ⚠==


# Text Elements
kill(信号值) ^EgdrzoZT

进程A ^ycIqCppZ

进程B ^nNeD3iRe

signal_handler ^RI99OW42

内核 ^CoZHPu7o

硬件 ^ZOdCNOXa

外设中断 ^WVEqptx7

忽略/转发/产生信号 OR 杀死进程 ^CLT6RDPK

s信号 ^4FXrw53J

s信号 ^Oo1ers8x

(1) 进程B通过sigaction建立signal_handler，
     并可通过sigprocmask屏蔽某些信号;
(2) 进程A通过kill发送信号,内核先收到信号;
(3) 内核跳转到进程B的signal_handler执行;
(4) signal_handler返回前执行sigreturn,完成
     清除栈帧,恢复到被打断处继续执行。 ^MK7bIbBt

信号处理流程 ^SCkCwxYD

(2) ^17ky1H68

(1) ^KJM6x1aN

被打断的正常执行处 ^M6Hk45jD

(4) ^cfz5if8E

(3) ^dbE2Ip4T

%%
# Drawing
```json
{
	"type": "excalidraw",
	"version": 2,
	"source": "https://excalidraw.com",
	"elements": [
		{
			"type": "rectangle",
			"version": 100,
			"versionNonce": 87192068,
			"isDeleted": false,
			"id": "IEYXgCiy7mt9WSbBSngRk",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -331.0052490234375,
			"y": -248.33331298828125,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 154.66668701171875,
			"height": 98.66665649414062,
			"seed": 1580253825,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294647,
			"link": null
		},
		{
			"type": "rectangle",
			"version": 72,
			"versionNonce": 1927847996,
			"isDeleted": false,
			"id": "Q94eWxKWUhtcvdJI3WjOg",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -313.0052490234375,
			"y": -229.66665649414062,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 121.99999999999999,
			"height": 41.333343505859375,
			"seed": 467168559,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294647,
			"link": null
		},
		{
			"type": "text",
			"version": 49,
			"versionNonce": 94212484,
			"isDeleted": false,
			"id": "EgdrzoZT",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -306.0052490234375,
			"y": -216,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 113,
			"height": 22,
			"seed": 249884975,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "TDBk6AyrwrZmGaqfnUSbn",
					"type": "arrow"
				}
			],
			"updated": 1650980294648,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "kill(信号值)",
			"rawText": "kill(信号值)",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "kill(信号值)"
		},
		{
			"type": "text",
			"version": 21,
			"versionNonce": 1507932348,
			"isDeleted": false,
			"id": "ycIqCppZ",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -277.0052490234375,
			"y": -281,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 50,
			"height": 22,
			"seed": 399306895,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "进程A",
			"rawText": "进程A",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "进程A"
		},
		{
			"type": "rectangle",
			"version": 255,
			"versionNonce": 389475900,
			"isDeleted": false,
			"id": "cyimDI6N2T8UgRX5TdmCF",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -126.33865356445314,
			"y": -249.66664123535156,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 241,
			"height": 98.66665649414062,
			"seed": 1883183361,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "GbprMboqY8QPFFkf_2P5h",
					"type": "arrow"
				}
			],
			"updated": 1650980927573,
			"link": null
		},
		{
			"type": "rectangle",
			"version": 252,
			"versionNonce": 487272196,
			"isDeleted": false,
			"id": "OpmFW0gcWaMLsVQgPN1IK",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -56.671966552734375,
			"y": -241.99998474121094,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 151.33331298828125,
			"height": 36.666656494140625,
			"seed": 161198991,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"type": "text",
					"id": "RI99OW42"
				},
				{
					"id": "GbprMboqY8QPFFkf_2P5h",
					"type": "arrow"
				},
				{
					"id": "TGvHzWHePYxgJsCpuROll",
					"type": "arrow"
				}
			],
			"updated": 1650980982387,
			"link": null
		},
		{
			"type": "text",
			"version": 81,
			"versionNonce": 1531052164,
			"isDeleted": false,
			"id": "nNeD3iRe",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -31.338592529296875,
			"y": -288.33335876464844,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 50,
			"height": 22,
			"seed": 1981573551,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "进程B",
			"rawText": "进程B",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "进程B"
		},
		{
			"type": "text",
			"version": 97,
			"versionNonce": 548860860,
			"isDeleted": false,
			"id": "RI99OW42",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -51.671966552734375,
			"y": -234.66665649414062,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 141.33331298828125,
			"height": 22,
			"seed": 646744943,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980935388,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "signal_handler",
			"rawText": "signal_handler",
			"baseline": 18,
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "OpmFW0gcWaMLsVQgPN1IK",
			"originalText": "signal_handler"
		},
		{
			"type": "rectangle",
			"version": 89,
			"versionNonce": 1068978180,
			"isDeleted": false,
			"id": "gWCMkeHZspvjvEO9ynmgN",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -329.0052490234375,
			"y": -139,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 445.3333740234375,
			"height": 68.66668701171875,
			"seed": 1118663631,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null
		},
		{
			"type": "text",
			"version": 65,
			"versionNonce": 908632636,
			"isDeleted": false,
			"id": "CoZHPu7o",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -315.671875,
			"y": -132.66665649414062,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 40,
			"height": 22,
			"seed": 483688353,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "内核",
			"rawText": "内核",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "内核"
		},
		{
			"type": "rectangle",
			"version": 82,
			"versionNonce": 399945604,
			"isDeleted": false,
			"id": "m4yyWq0hiw9dy8FHuZGmj",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -327.0052490234375,
			"y": -58.33331298828125,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 439,
			"height": 38.6666259765625,
			"seed": 1268736577,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"type": "text",
					"id": "ZOdCNOXa"
				}
			],
			"updated": 1650980294648,
			"link": null
		},
		{
			"type": "text",
			"version": 29,
			"versionNonce": 2043738812,
			"isDeleted": false,
			"id": "ZOdCNOXa",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -322.0052490234375,
			"y": -50,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 429,
			"height": 22,
			"seed": 395289167,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "硬件",
			"rawText": "硬件",
			"baseline": 18,
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "m4yyWq0hiw9dy8FHuZGmj",
			"originalText": "硬件"
		},
		{
			"type": "line",
			"version": 49,
			"versionNonce": 64888580,
			"isDeleted": false,
			"id": "pRLpLY0G9baAOxel-i_mV",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -365.0052490234375,
			"y": -63.666656494140625,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 520.666748046875,
			"height": 2.666656494140625,
			"seed": 843236001,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					520.666748046875,
					-2.666656494140625
				]
			]
		},
		{
			"type": "line",
			"version": 145,
			"versionNonce": 1205486396,
			"isDeleted": false,
			"id": "IeCzOeO0ZQF1GE-Wj3dVf",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -378.6719970703125,
			"y": -142.0000457763672,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 520.666748046875,
			"height": 2.666656494140625,
			"seed": 1193635745,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					520.666748046875,
					-2.666656494140625
				]
			]
		},
		{
			"type": "arrow",
			"version": 317,
			"versionNonce": 1816895108,
			"isDeleted": false,
			"id": "qHrSJSrvMG44x2npduRtK",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -13.671875000000004,
			"y": -41.333343505859375,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 44.6666259765625,
			"height": 48.4235621830837,
			"seed": 818046735,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650980294648,
			"link": null,
			"startBinding": null,
			"endBinding": {
				"elementId": "WVEqptx7",
				"focus": 0.829527661408653,
				"gap": 12.350983610899561
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					44.6666259765625,
					-31.333343505859375
				],
				[
					27.315581330506692,
					-48.4235621830837
				]
			]
		},
		{
			"type": "text",
			"version": 162,
			"versionNonce": 111573948,
			"isDeleted": false,
			"id": "WVEqptx7",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 25.99468994140625,
			"y": -91,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 80,
			"height": 22,
			"seed": 493486017,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "qHrSJSrvMG44x2npduRtK",
					"type": "arrow"
				}
			],
			"updated": 1650980294649,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "外设中断",
			"rawText": "外设中断",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "外设中断"
		},
		{
			"type": "rectangle",
			"version": 297,
			"versionNonce": 46719492,
			"isDeleted": false,
			"id": "g-stbP-toqm34mE2_7kK1",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -189.0052490234375,
			"y": -129.33331298828125,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 200.33331298828125,
			"height": 54,
			"seed": 1683856591,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"type": "text",
					"id": "CLT6RDPK"
				},
				{
					"id": "TDBk6AyrwrZmGaqfnUSbn",
					"type": "arrow"
				},
				{
					"id": "GbprMboqY8QPFFkf_2P5h",
					"type": "arrow"
				},
				{
					"id": "Y5XCXuIODXdVvSmiXxQnM",
					"type": "arrow"
				},
				{
					"id": "S42PnNbgqR4UO0p0CBQFM",
					"type": "arrow"
				},
				{
					"id": "ZRkLu4dIrPEHIP34aRD9i",
					"type": "arrow"
				},
				{
					"id": "zLiBn57fh0q2sCRhIHs4G",
					"type": "arrow"
				}
			],
			"updated": 1650981069814,
			"link": null
		},
		{
			"type": "text",
			"version": 336,
			"versionNonce": 1722364476,
			"isDeleted": false,
			"id": "CLT6RDPK",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -184.0052490234375,
			"y": -124.33331298828125,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 190.33331298828125,
			"height": 44,
			"seed": 2134908993,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650981097641,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "忽略/转发/产生信号 \nOR 杀死进程",
			"rawText": "忽略/转发/产生信号 OR 杀死进程",
			"baseline": 40,
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "g-stbP-toqm34mE2_7kK1",
			"originalText": "忽略/转发/产生信号 OR 杀死进程"
		},
		{
			"type": "arrow",
			"version": 369,
			"versionNonce": 731337020,
			"isDeleted": false,
			"id": "TDBk6AyrwrZmGaqfnUSbn",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -237.671875,
			"y": -191,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 47.6666259765625,
			"height": 78.8367316062225,
			"seed": 1159298849,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650981097640,
			"link": null,
			"startBinding": {
				"elementId": "EgdrzoZT",
				"focus": -0.15552935253866182,
				"gap": 3
			},
			"endBinding": {
				"elementId": "g-stbP-toqm34mE2_7kK1",
				"gap": 1,
				"focus": -0.4448332929345587
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					12.6666259765625,
					65.33334350585938
				],
				[
					47.6666259765625,
					78.8367316062225
				]
			]
		},
		{
			"type": "arrow",
			"version": 617,
			"versionNonce": 2033086596,
			"isDeleted": false,
			"id": "GbprMboqY8QPFFkf_2P5h",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -152.1799949565844,
			"y": -132.33362748715234,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 94.20342161156564,
			"height": 74.52536190540597,
			"seed": 202355169,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650981097640,
			"link": null,
			"startBinding": {
				"elementId": "g-stbP-toqm34mE2_7kK1",
				"gap": 3.0003144988710915,
				"focus": -0.6505799581868228
			},
			"endBinding": {
				"elementId": "Oo1ers8x",
				"focus": -0.5273070724418046,
				"gap": 13.195332172559361
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					5.461385307624378,
					-37.21086118333376
				],
				[
					94.20342161156564,
					-74.52536190540597
				]
			]
		},
		{
			"type": "text",
			"version": 413,
			"versionNonce": 1312035076,
			"isDeleted": false,
			"id": "4FXrw53J",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -237.83859252929688,
			"y": -111.83334350585938,
			"strokeColor": "#862e9c",
			"backgroundColor": "transparent",
			"width": 39,
			"height": 17,
			"seed": 2015080655,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980704404,
			"link": null,
			"fontSize": 16,
			"fontFamily": 4,
			"text": "s信号",
			"rawText": "s信号",
			"baseline": 15,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "s信号"
		},
		{
			"type": "text",
			"version": 515,
			"versionNonce": 121664516,
			"isDeleted": false,
			"id": "Oo1ers8x",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -114.17190551757812,
			"y": -211.54667236328126,
			"strokeColor": "#862e9c",
			"backgroundColor": "transparent",
			"width": 43,
			"height": 19,
			"seed": 124883759,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "GbprMboqY8QPFFkf_2P5h",
					"type": "arrow"
				}
			],
			"updated": 1650981018839,
			"link": null,
			"fontSize": 17.466662597656246,
			"fontFamily": 4,
			"text": "s信号",
			"rawText": "s信号",
			"baseline": 16,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "s信号"
		},
		{
			"type": "text",
			"version": 697,
			"versionNonce": 636335164,
			"isDeleted": false,
			"id": "MK7bIbBt",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -296.79762956015765,
			"y": -440.0000305175781,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 397,
			"height": 132,
			"seed": 761102012,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980753974,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "(1) 进程B通过sigaction建立signal_handler，\n     并可通过sigprocmask屏蔽某些信号;\n(2) 进程A通过kill发送信号,内核先收到信号;\n(3) 内核跳转到进程B的signal_handler执行;\n(4) signal_handler返回前执行sigreturn,完成\n     清除栈帧,恢复到被打断处继续执行。",
			"rawText": "(1) 进程B通过sigaction建立signal_handler，\n     并可通过sigprocmask屏蔽某些信号;\n(2) 进程A通过kill发送信号,内核先收到信号;\n(3) 内核跳转到进程B的signal_handler执行;\n(4) signal_handler返回前执行sigreturn,完成\n     清除栈帧,恢复到被打断处继续执行。",
			"baseline": 128,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "(1) 进程B通过sigaction建立signal_handler，\n     并可通过sigprocmask屏蔽某些信号;\n(2) 进程A通过kill发送信号,内核先收到信号;\n(3) 内核跳转到进程B的signal_handler执行;\n(4) signal_handler返回前执行sigreturn,完成\n     清除栈帧,恢复到被打断处继续执行。"
		},
		{
			"type": "rectangle",
			"version": 81,
			"versionNonce": 1511981500,
			"isDeleted": false,
			"id": "g2XB-wA296t7KsdHcD86p",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -294.29762956015765,
			"y": -445.83336639404297,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 390.33331298828125,
			"height": 139.3333282470703,
			"seed": 58158524,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980556956,
			"link": null
		},
		{
			"type": "text",
			"version": 50,
			"versionNonce": 145623684,
			"isDeleted": false,
			"id": "SCkCwxYD",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -173.9643165718764,
			"y": -478.50003814697266,
			"strokeColor": "#000000",
			"backgroundColor": "transparent",
			"width": 120,
			"height": 22,
			"seed": 132147076,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980572989,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "信号处理流程",
			"rawText": "信号处理流程",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "信号处理流程"
		},
		{
			"type": "arrow",
			"version": 195,
			"versionNonce": 1267845564,
			"isDeleted": false,
			"id": "S42PnNbgqR4UO0p0CBQFM",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 100.85268517903485,
			"y": -161.2766170592456,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 85.81694071575498,
			"height": 50.83374525272356,
			"seed": 1001150396,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650981097640,
			"link": null,
			"startBinding": null,
			"endBinding": {
				"elementId": "g-stbP-toqm34mE2_7kK1",
				"gap": 3.707680498436119,
				"focus": 0.6187668571872006
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-85.81694071575498,
					50.83374525272356
				]
			]
		},
		{
			"type": "text",
			"version": 52,
			"versionNonce": 782554500,
			"isDeleted": false,
			"id": "17ky1H68",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -237.4643165718764,
			"y": -184.16669464111328,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 29,
			"height": 22,
			"seed": 49214084,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650980651851,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "(2)",
			"rawText": "(2)",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "(2)"
		},
		{
			"type": "text",
			"version": 472,
			"versionNonce": 1029903292,
			"isDeleted": false,
			"id": "KJM6x1aN",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 93.20237043984235,
			"y": -179.50000762939453,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 25,
			"height": 22,
			"seed": 908315524,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "Y5XCXuIODXdVvSmiXxQnM",
					"type": "arrow"
				},
				{
					"id": "S42PnNbgqR4UO0p0CBQFM",
					"type": "arrow"
				}
			],
			"updated": 1650980951445,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "(1)",
			"rawText": "(1)",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "(1)"
		},
		{
			"type": "rectangle",
			"version": 547,
			"versionNonce": 57138308,
			"isDeleted": false,
			"id": "aAfmEkL27roEuTTJ7JvFe",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -71.29750748984515,
			"y": -196.5000228881836,
			"strokeColor": "#087f5b",
			"backgroundColor": "transparent",
			"width": 127.66668701171878,
			"height": 20.666656494140632,
			"seed": 1297569540,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [],
			"updated": 1650981055938,
			"link": null
		},
		{
			"type": "text",
			"version": 376,
			"versionNonce": 1973277316,
			"isDeleted": false,
			"id": "M6Hk45jD",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -67.5524271029542,
			"y": -192.50003814697266,
			"strokeColor": "#087f5b",
			"backgroundColor": "transparent",
			"width": 121,
			"height": 15,
			"seed": 642253188,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "TGvHzWHePYxgJsCpuROll",
					"type": "arrow"
				},
				{
					"id": "ZRkLu4dIrPEHIP34aRD9i",
					"type": "arrow"
				},
				{
					"id": "zLiBn57fh0q2sCRhIHs4G",
					"type": "arrow"
				}
			],
			"updated": 1650981069814,
			"link": null,
			"fontSize": 13.490191291360302,
			"fontFamily": 4,
			"text": "被打断的正常执行处",
			"rawText": "被打断的正常执行处",
			"baseline": 12,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "被打断的正常执行处"
		},
		{
			"type": "text",
			"version": 579,
			"versionNonce": 254657668,
			"isDeleted": false,
			"id": "cfz5if8E",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 64.36899641640485,
			"y": -204.16669464111328,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 29,
			"height": 22,
			"seed": 215356932,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "Y5XCXuIODXdVvSmiXxQnM",
					"type": "arrow"
				},
				{
					"id": "S42PnNbgqR4UO0p0CBQFM",
					"type": "arrow"
				}
			],
			"updated": 1650980990304,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "(4)",
			"rawText": "(4)",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "(4)"
		},
		{
			"type": "arrow",
			"version": 308,
			"versionNonce": 422785284,
			"isDeleted": false,
			"id": "TGvHzWHePYxgJsCpuROll",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 91.35270167525093,
			"y": -204.3333282470703,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 102.98364422368982,
			"height": 76.16663360595703,
			"seed": 917301692,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650981097637,
			"link": null,
			"startBinding": {
				"elementId": "OpmFW0gcWaMLsVQgPN1IK",
				"gap": 1,
				"focus": -0.9600158293842603
			},
			"endBinding": {
				"elementId": "M6Hk45jD",
				"focus": -0.139329000331144,
				"gap": 6
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-4.983644223689822,
					30.499977111816406
				],
				[
					-102.98364422368982,
					76.16663360595703
				],
				[
					-92.87980710664506,
					32.833290100097656
				]
			]
		},
		{
			"type": "text",
			"version": 578,
			"versionNonce": 1417203844,
			"isDeleted": false,
			"id": "dbE2Ip4T",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -88.4643165718764,
			"y": -228.50003814697266,
			"strokeColor": "#c92a2a",
			"backgroundColor": "transparent",
			"width": 27,
			"height": 22,
			"seed": 1286971068,
			"groupIds": [],
			"strokeSharpness": "sharp",
			"boundElements": [
				{
					"id": "Y5XCXuIODXdVvSmiXxQnM",
					"type": "arrow"
				},
				{
					"id": "GbprMboqY8QPFFkf_2P5h",
					"type": "arrow"
				}
			],
			"updated": 1650981027504,
			"link": null,
			"fontSize": 20,
			"fontFamily": 4,
			"text": "(3)",
			"rawText": "(3)",
			"baseline": 18,
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "(3)"
		},
		{
			"type": "arrow",
			"version": 169,
			"versionNonce": 1184219140,
			"isDeleted": false,
			"id": "zLiBn57fh0q2sCRhIHs4G",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -51.297629560157645,
			"y": -175.8333511352539,
			"strokeColor": "#087f5b",
			"backgroundColor": "transparent",
			"width": 98.42624811235197,
			"height": 45.500038146972656,
			"seed": 1753351740,
			"groupIds": [],
			"strokeSharpness": "round",
			"boundElements": [],
			"updated": 1650981097640,
			"link": null,
			"startBinding": {
				"elementId": "M6Hk45jD",
				"focus": 0.5836659727449881,
				"gap": 1.66668701171875
			},
			"endBinding": {
				"elementId": "g-stbP-toqm34mE2_7kK1",
				"gap": 1,
				"focus": -0.8639411212519262
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-20.66668701171875,
					31.33331298828125
				],
				[
					-98.42624811235197,
					45.500038146972656
				]
			]
		}
	],
	"appState": {
		"theme": "light",
		"viewBackgroundColor": "#ffffff",
		"currentItemStrokeColor": "#087f5b",
		"currentItemBackgroundColor": "transparent",
		"currentItemFillStyle": "hachure",
		"currentItemStrokeWidth": 1,
		"currentItemStrokeStyle": "solid",
		"currentItemRoughness": 1,
		"currentItemOpacity": 100,
		"currentItemFontFamily": 4,
		"currentItemFontSize": 16,
		"currentItemTextAlign": "left",
		"currentItemStrokeSharpness": "sharp",
		"currentItemStartArrowhead": null,
		"currentItemEndArrowhead": "arrow",
		"currentItemLinearStrokeSharpness": "round",
		"gridSize": null
	},
	"files": {}
}
```
%%