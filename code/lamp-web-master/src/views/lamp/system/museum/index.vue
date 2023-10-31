<template>
<div :style="{ backgroundImage: 'url('+ imageUrl +')' }">

<br/><br/><br/><br/><br/><br/><br/>
<center :style="{fontSize: topicfontSize }">TEST</center>  
<br/><br/><br/><br/>
<center :style="{fontSize: fontSize }">今日访客{{todayVisitors}}</center>  
<br/><br/>
<center :style="{fontSize: fontSize }">馆内人数{{currentNums}}          本月访客{{monthNums}}</center>
<br/><br/>
<center :style="{fontSize: fontSize }">今年访客{{yearNums}}          历史访客{{historys}}</center>
<br/><br/><br/>


<center :style="{fontSize: fontSize }">区域{{id}}</center>
<center :style="{fontSize: fontSize }">区域今日访客{{areatodayVisitors}}</center>
<center :style="{fontSize: fontSize }">区域实时人数{{areacurrentNums}}</center>
<center :style="{fontSize: fontSize }">区域本月访客{{areamonthNums}}</center>
<center :style="{fontSize: fontSize }">区域本年访客{{areayearNums}}</center>
<center :style="{fontSize: fontSize }">区域历史访客{{areahistorys}}</center>

<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>
</div>
  </template>

<script>

export default {
  name: 'testComponent',
  data(){
 
    return {
    
      todayVisitors : 0,
      currentNums : 0,
      monthNums : 0,
      yearNums : 0,
      historys : 0,

      
      id : [],
      areatodayVisitors : [],
      areacurrentNums : [],
      areayearNums : [],
      areahistorys : [],
      areamonthNums : [],
     

      topicfontSize:"60px",
      fontSize:"28px",
      imageUrl: require('@/assets/picture.png'),
      intervalId:null,
      
    }
},
mounted() {
    this.getVisitors();
    this.currentNum();
    this.history();
    this.monthNum();
    this.yearNum(); // 在组件加载完成后发送API请求
    this.getId();
    this.areacurrentNum();
    this.areayearNum();
    this.areahistory();
    this.areamonthNum();
    this.areagetVisitors();
   
  },
  
created(){
   this.dataRefreh();
},
unmounted() {
   // 销毁组件之前，清除计时器
   this.clear();
},
  methods:{
    getVisitors(){
      this.$axios({method:'get',
url:'/api/data/miniute/todayVisitor'}).then(response => {
      if(response.data.data == null)
          this.todayVisitors = 0;
        else  
        this.todayVisitors=response.data.data;
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

    areagetVisitors(){
      this.$axios({method:'get',
url:'/api/data/area/dayCount'}).then(response => {
      if(response.data.data== null)
          this.areatodayVisitors = 0;
        else  
      
        for (var count= 0 ; count < response.data.data.length ; count++){

          this.areatodayVisitors.push(response.data.data[count]['dayCount']);

}
      
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

    getId(){
      this.$axios({method:'get',
url:'/api/data/area/dayCount'}).then(response => {
      if(response.data.data== null)
          this.areatodayVisitors = 0;
        else  
      
        this.id =  response.data.data.length;
      
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },
currentNum(){
  this.$axios.get('/api/data/miniute/currentNum').then(response => {
          this.currentNums = response.data.data;
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

    areacurrentNum(){
  this.$axios.get('/api/data/area/currentCount').then(response => {

    for(var count= 0 ; count < response.data.data.length ; count++){

this.areacurrentNums.push(response.data.data[count]['currentCount']);

}
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },
history(){
  this.$axios.get('/api/data/month/history') .then(response => {
          this.historys = response.data.data;
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },
    areahistory(){
  this.$axios.get('/api/data/area/historyCount') .then(response => {
  
          for(var count= 0 ; count< response.data.data.length ; count++){

            this.areahistorys.push(response.data.data[count]['yearCount']);
          
          }
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

monthNum(){
  this.$axios({method:'get',
url:'/api/data/month/monthNum'}) .then(response => {
          this.monthNums = response.data.data;
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },
    areamonthNum(){
  this.$axios({method:'get',
url:'/api/data/area/monthCount'}) .then(response => {
  for(var count= 0 ; count< (response.data.data).length ; count++){
            this.areamonthNums.push(response.data.data[count]['monthCount']);
          }

          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

yearNum(){
  this.$axios.get('/api/data/month/yearNum').then(response => {
          this.yearNums = response.data.data;
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

    areayearNum(){
  this.$axios.get('/api/data/area/yearCount').then(response => {
       
          for(var count= 0 ; count< (response.data.data).length ; count++){
            this.areayearNums.push(response.data.data[count]['yearCount']);
          }

          //this.areayearNums = response.data.data;
          console.log(response)
            //在这里编写请求发送成功后后端传送回来的数据，存在response里，你用console查看
            })
           .catch(error => {
console.error(error)
	//这里是请求失败后的处理，相关信息在error里
	})
    },

    dataRefreh() {
     // 计时器正在进行中，退出函数
     if (this.intervalId != null) {
        return;
     }
      // 计时器为空，操作
      this.intervalId = setInterval(() => {
         console.log("刷新" + new Date());
         this.dataRefreh();
         this.$router.go(0)  //每1分钟调用方法刷新一次页面，进行数据更新
        }, 60000);
      }, 
      // 停止定时器
      clear() {
        clearInterval(this.intervalId);//清除计时器
        this.intervalId = null; //设置为null
      }

  }
}
</script>