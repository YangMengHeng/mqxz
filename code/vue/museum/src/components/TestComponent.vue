<template>
  <div id="test">
    <el-row>
      <el-col :span="24">
        <el-container>

          <el-card id="headerMenuCard">
            <el-header id="headerMenu">
              <el-row>
                <el-col :span="3">
                  <i class="el-icon-video-camera-solid"></i>
                  <span id="leftTaskTitle">视频追踪</span>
                </el-col>
                <el-col :span="6">
                  <el-upload
                  ref="upload"
                  :action=serverUrl
                  :file-list="fileList"
                  :auto-upload="false"
                  :on-change="handleUploadFileChange"
                  :on-remove="handleUploadFileRemove">
                  <el-button slot="trigger" type="primary">上传追踪者照片</el-button>
                  <el-button style="margin-left: 10px;" type="success" @click="submitUpload">提交追踪任务</el-button>
                  <div slot="tip" class="el-upload__tip">只能上传jpg/png文件，且不超过2MB</div>
                  </el-upload>
                </el-col>

                <el-col :span="4">
                  <el-button type="info" plain @click="tmpQuery">任务状态（点击刷新）：{{taskStatus[taskIndex]}}</el-button>
                </el-col>

                <el-col :span="1">
                  <el-date-picker
                    v-model="value2"
                    type="datetimerange"
                    :picker-options="pickerOptions"
                    range-separator="至"
                    start-placeholder="开始日期"
                    end-placeholder="结束日期"
                    align="right">
                  </el-date-picker>
                </el-col>
              </el-row>
            </el-header>
          </el-card>

        </el-container>
      </el-col>
    </el-row>

    <el-row>
      <el-container id="mainContainer">

            <el-main>
              <el-card id="mapImageCard">
                <div :id="index"
                  v-for="(item, index) in cameraPos"
                  :key="index"
                  class="cameraDiv"
                  :style="{left:item[0] + 'px', top:item[1] + 'px'}"
                  >
                  <el-popover
                  placement="top-start"
                  title=""
                  width="200"
                  trigger="click"
                  >
                    <i icon="el-icon-video-camera-solid"></i>
                    <el-button
                      slot="reference"
                      class="camera"
                      circle=""
                      icon="el-icon-video-camera-solid"
                      >
                    </el-button>
                  </el-popover>
                </div>
                <img :src=mapImageUrl id="mapIamge">
              </el-card>
            </el-main>
        </el-container>
    </el-row>
  </div>
</template>

<script>
import LeaderLine from 'leader-line'

export default {
  name: 'TestComponent',
  props: {},
  data() {
    let isTaskBegin = false
    let cameraPos = []
    let mapImageUrl = ''
    let imageList = []
    let fileList = []
    let serverUrl = ''
    let taskStatus = [
      '未开始',
      '正在追踪',
      '已完成'
    ]
    let taskIndex = 0
    let progressPercent = 0
    let timeout = 10000
    let taskID = []
    let intervalList = []

      return {isTaskBegin, cameraPos, mapImageUrl, imageList, fileList, serverUrl, taskID, taskStatus, taskIndex, progressPercent, timeout, intervalList}
  },
  methods: {
    cameraInitiation(){
      let camera = [
        [520, 330],
        [900, 430],
        [1160, 420],
        [500, 680],
        [730, 680]
      ]

      // console.log('camera', camera)

      return camera
    },

    mapInitiation(){
      return require('../assets/map.png')
    },

    createRandom(range, nums){
      let uuid = ''
      for(let i = 0; i < nums; i++){
        let t = Math.floor(Math.random() * range)
        uuid = uuid.concat(t.toString(10))
      }
      // console.log('uuid', uuid)

      return uuid
    },

    trackObject(){
      console.log('trackobject')
      let cameraDom = [document.getElementById('0'),
    document.getElementById('1'),
    document.getElementById('2'),
    document.getElementById('3'),
    document.getElementById('4')]

    console.log('cameraDom', cameraDom)

    let pos = [0, 3, 4, 1, 2]
    for(let i = 0; i < 4; i++){
      new LeaderLine(LeaderLine.pointAnchor(cameraDom[pos[i]],{
        x: 70,
        y: 30
      }),
      LeaderLine.pointAnchor(cameraDom[pos[i + 1]],{
        x: -10,
        y: 30
      }),
      {color: 'red', size: 8})
    }

    console.log('down.......')

      return true
    },

    createTask(tmpFileList){
      console.log('createTask')
      console.log('tmpFileList', tmpFileList)
      // 在这里创建任务，把后端需要的数据进行组装打包发过去
      let transferData = {
        'task': this.createRandom(10, 16),
        'file': tmpFileList[0],
      }
      console.log('transferData', transferData)
      // 记得要发送axios请求到后端
      let tmp = {
      'taskName': 'test1',
      'taskImgs': 'https://img95.699pic.com/photo/50147/2119.jpg_wh860.jpg'
      }
      this.$axios({
      url:"http://192.168.1.171:8080/task/handleTask",
      method:"post",
      data: tmp,
      }).then(response=>{
        console.log('success', response)
      }).catch(error=>{
        console.log('error', error)
      });
    console.log('down ...................')

      return transferData['task']
    },

    tmpQuery(){
      console.log('tmpQuery')

      if(this.taskStatus[this.taskIndex] == '未开始'){
        this.$message.error("任务未提交！请检查上传的照片！")
        return
      }

      this.taskIndex = 2

      if(this.taskStatus[this.taskIndex] == '已完成'){
        this.$message({
          message: '刷新成功！任务已完成！请查看视频轨迹！',
          type: 'success'
        })
        this.trackObject()
      }
      else{
        let t = this.getTaskResult()
        console.log('get task', t)
      }
    },

    queryTask(task){
      console.log('queryTask', task)
      let currentTime = Date.now()

      this.progressPercent = setInterval(this.taskPoll, 1000, task, currentTime)
      this.intervalList.push(this.progressPercent)

      return true
    },

    taskPoll(task, curTime){
      console.log('taskPoll', task)
      // console.log('curTime', curTime)
      let lastTime = 0
      // console.log('before', this.progressPercent)

      // 封装axios请求
      this.progressPercent = this.progressPercent + Math.round(Math.random() * 10)
      // console.log('after', this.progressPercent)

      // 判断任务是否已经完成
      if(this.progressPercent >= 100){
        this.intervalList.forEach((item) =>{
          clearInterval(item)
        })
        this.intervalList = []
        this.progressPercent = 100
        this.taskIndex = 2

        return true
      }

      lastTime = Date.now()
      console.log('lastTime', lastTime)
      if((lastTime - curTime) > this.timeout){
        this.intervalList.forEach((item) =>{
          clearInterval(item)
        })
        this.intervalList = []
        this.progressPercent = 0
        this.taskIndex = 0
        this.$message.error('任务处理超时失败！请检查网络！')
        return false
      }
    },

    getTaskResult(){
      console.log('getTaskResult')
      let order = []

      this.$axios.get("http://192.168.1.171:16855/result/results")
      .then(response=>{
        console.log('success................', response)
        order = [response.data.data[0].resId, response.data.data[1].resId,
      response.data.data[2].resId,
      response.data.data[3].resId,
      response.data.data[4].resId]
      this.taskIndex = 2
      this.$message({
          message: '刷新成功！任务已完成！请查看视频轨迹！',
          type: 'success'
        })
        console.log('order', order)
      }).catch(error=>{
        console.log('error', error)
        this.$message.error('刷新成功！任务还未完成！请稍后！')
      });
    },

    handleUploadFileChange(file, fileList){
      console.log('handleUploadFileChange', file)
      // console.log('fileList', fileList)
      this.fileList = fileList
      // console.log('fileList', fileList)
    },

    handleUploadFileRemove(file, fileList){
      console.log('handleUploadFileRemove', file)
      // console.log('fileList', fileList)
      this.fileList = fileList
      // console.log('fileList', fileList)
    },

    submitUpload(){
      console.log('submit')
      console.log('fileList', this.fileList)
      let tmpTaskID
      if(this.fileList.length == 0){
        this.$message.error('开始追踪任务前请提交追踪者照片！')
        return
      }

      if((tmpTaskID = this.createTask(this.fileList)) != false){
        // console.log('success!')
        this.taskIndex = 1
        this.$message({
          message: '追踪任务提交成功！请勿离开当前页面否则任务失败！',
          type: 'success'
        })
        this.taskID.push(tmpTaskID)
      }
      console.log('taskID', this.taskID)

      // if(this.queryTask(this.taskID) == true){
      //   console.log('success!')
      // }

      // if(this.getTaskResult() == true){
      //   console.log('success!')
      // }
    },
  },

  beforeCreate(){
    // console.log('beforeCreate')
  },

  created(){
    console.log('created')
    this.mapImageUrl = this.mapInitiation()
    // console.log('mapImageUrl', this.mapImageUrl)
    this.cameraPos = this.cameraInitiation()
    // console.log('cameraPos', this.cameraPos)
  },
}
</script>

<style scoped>
#test{
  font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
}

#headerMenuCard{
  width: 100%;
  font-size: 20px;
  margin: 20px 20px 0 20px;
}

#headerMenu{
  text-align: left;
  padding: 0;
}

#mapIamge{
  width: 100%;
  display: block;
  z-index: 0;
  position: relative;
}

.camera{
  position: absolute;
  font-size: 40px;
}

.cameraDiv{
  position: relative;
  display: block;
  width: 100%;
  height: 100%;
  z-index: 90;
}

.leader-line{
  z-index: 999
}
</style>
