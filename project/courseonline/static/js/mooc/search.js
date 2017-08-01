/**
 * search 
 * @author zhoujq
 *
 */
	 
define(function(require, exports, module){
	
	module.exports = {
		
		// 变量初始化
		currIndex: -1,
		areaPanel: $('.js-search-area-prge'),
		input: $('.js-search-ipt'),
		
		// 搜索结果键盘切换功能
		keyup: function (key){
			if( $('.js-search-area-prge').is('hidden') ) return;
			
			if( key == 40){
				// 下
				this.setCurrIndex('down')
				this.itemSwitch()
			}
			
			if( key == 38){
				// 上
				this.setCurrIndex('up')
				this.itemSwitch()
			}
		},
		
		setCurrIndex: function(direction) { // 设置序号
			var items = this.areaPanel.find('li'),
				itemsCount = items.length;

			if (direction === 'up') {
				this.currIndex = this.currIndex > -1 ? this.currIndex - 1 : itemsCount - 1;
			} else {
				this.currIndex = this.currIndex < itemsCount - 1 ? this.currIndex + 1 : -1;
			}
		},
		
		itemSwitch: function() { // 搜索结果项切换
			var $items = this.areaPanel.find('li'),
				$currentItem = null,
				currentKey = '';

			$items.removeClass('active');

			if (this.currIndex > -1) {
				$currentItem = $items.eq( this.currIndex );
				$currentItem.addClass('active');

				currentKey = $currentItem.find('a').html();
				this.setTriggerValue( currentKey );
			}
		},
		
		setTriggerValue: function(key) { // 设置搜索框的值
			this.input.val(key);
		},
	 	
		// 联想搜索功能 ajax
		associative: function ( value ){
			var self = this;
			$.ajax({
				type: "GET",
				url: "/search/history?words="+value,
				dataType: "json",
				success: function(res) {
					if( res.data.length > 0 ){
						if( self.input.val() == '' ) return;// 防止冲突
						var dom = self.searchAreaDom( res.data )
						self.area.$area.html(dom);
						self.area.show();
					}else{
						self.area.hide();
					}
				}
			});
		},
		
		// 获取页面初始化搜索结果
		words: function (){
			//return this.getUrlQuery('words');
			return OP_CONFIG.$words;
		},
		
		/*
		 * 跳转到具体的搜索页面 @全站 @课程 @猿问 @手记
		 */
		location: function (pager, words){
			
			if( typeof words == 'undefined' ){
				words = pager;
				pager = '';
			}
			
			if( words == '' ) words = this.words();
			location.href = this.returnUrl(pager) + encodeURIComponent(words);
		},
		
		// 筛选具体搜索页面的url
		returnUrl : function (pager){
			var url = '';
			switch( pager ){
				
				case 'index':
					url = '/search/?words=';
				break;
				case 'course':
					url = '/search/course?words=';
				break;
				case 'wenda':
					url = '/search/wenda?words=';
				break;
				case 'article':
					url = '/search/article?words=';
				break;
				default:
					url = '/search/?words=';
			}
			return url;
		},
		
		// 工具类 获取url Query 参数
		getUrlQuery: function ( keyName ){
			var url = window.location.href;
			var pos = url.indexOf('?');

			if (pos !== -1) {
				var subUrl = url.substring(pos + 1);
				var temparr = subUrl.split('&');
				
				var str = '{';
				for( var i=0; i<temparr.length; i++){
					 str += '"'+temparr[i].replace('=', '":"') + '"';	
				}
				str+='}';
				var json = JSON.parse(str);
				
				return json[''+ keyName +''];
			}
		},
		
		/*
		 * 是否有历史搜索
		 * is true : 已请求过历史搜索
		 * dom : 历史搜索结果存在本地 不用多次请求历史搜索接口
		 */
		History: {
			is: false,
			dom: ''
		},
		
		// 实时搜索内容dom拼接
		searchAreaDom: function (data, first){
			var str = '';
			
			if( first ){
				str += '<li class="first">';
					str += '<span>最近搜索</span>';
					//str += '<span class="del-history js-del-history">清空历史</span>';
				str += '</li>';
			}
			
			for(var i=0; i<data.length; i++){
				str += '<li><a href="/search/?words='+data[i].word+'">'+ data[i].word +'</a></li>'
			}
			return str;
		},
		
		setSearchHistory: function (){
			var self = this;
			var area = $('.js-search-area-prge');
			
			if(!isLogin){
				return false;
			}
			
			if( self.History.is && self.History.dom == '' ){
				return;
			}
			
			if( self.History.is ){
				area.html( self.History.dom );
				self.area.show();
				return;
			}
			
			this.getSearchHistory( function (res){
				if( res.data.length > 0 ){
					var dom = self.searchAreaDom(res.data, true);
					area.html(dom);
					self.area.show();
					self.History.is = true;
					self.History.dom = dom;
				}
			})
		},
		
		// 实时搜索区域显示关闭接口
		area: {
			$area : $('.js-search-area-prge'),
			show: function (){
				this.$area.show()
			},
			hide: function (){
				this.$area.hide()
			}
		},
		
		getSearchHistory: function ( callback ) { // 最近的0-5条搜索记录
			var that = this;
			$.ajax({
				type: "GET",
				url: "/index/searchhistory",
				dataType: "json",
				success: function(res) {
					callback && callback(res)
				}
			});
		},
	}
})