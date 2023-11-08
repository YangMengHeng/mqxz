<template>
  <div id="test">
    <el-container>
      <el-aside id="leftMenu" width="330px">
        <el-container direction="vertical">
          <el-card ref="leftMenuCard">
            <el-row style="margin-top:20px">
              <i class="el-icon-video-camera-solid"></i>
              <span id="leftTaskTitle">轨迹追踪</span>
            </el-row>

            <el-row class="menuInterval">
              <el-button type="info" :loading=taskFlag disabled>任务状态：{{taskStatus[taskIndex]}}</el-button>
            </el-row>

            <el-row class="menuInterval">
              <el-upload
                ref="upload"
                :action=serverUrl
                :file-list="fileList"
                list-type="picture"
                :auto-upload="false"
                :show-file-list="true"
                :on-change="handleUploadFileChange"
                :on-remove="handleUploadFileRemove"
                >
                <el-button slot="trigger" type="plain" icon="el-icon-circle-plus-outline">上传追踪者照片</el-button>
                <el-row class="menuInterval">
                  <el-image :src=traceImage :style="{width: objectImgWidth,height:objectImgHeight}">
                    <div slot="placeholder" class="image-slot">
                      加载中<span class="dot">...</span>
                    </div>
                  </el-image>
                </el-row>
                <el-button type="success" @click="submitUpload"
                class="menuInterval"
                icon="el-icon-upload2"
                :disabled=isSubmitStatus>提交追踪任务</el-button>
                <div slot="tip" class="el-upload__tip">只能上传jpg/png文件，且不超过2MB</div>
              </el-upload>
            </el-row>
            <!-- <el-row>
              <el-button @click="test" :disabled=isSubmitStatus>test</el-button>
            </el-row> -->
          </el-card>
        </el-container>
      </el-aside>

      <el-main>
        <el-card id="mapImageCard" ref="mapImage">
          <el-row class="menuInterval">
              <el-date-picker
                v-model="timeValue"
                type="datetimerange"
                :picker-options="pickerOptions"
                range-separator="至"
                start-placeholder="开始日期"
                end-placeholder="结束日期"
                align="right">
              </el-date-picker>
            </el-row>
          <div
            v-for="(item, index) in cameraPos"
            :key="index"
            class="cameraDiv"
            :style="{left:item[0] + 'px', top:item[1] + 'px'}"
            :id="index + 1"
            >
            <el-popover
              placement="top-start"
              title=""
              width="200"
              trigger="click"
              >
                <i icon="el-icon-video-camera-solid"></i>
                <el-table :data="cameraGridData[index]">
                  <el-table-column width="150" property="startTime" label="开始时间"></el-table-column>
                  <el-table-column width="150" property="endTime" label="结束时间"></el-table-column>
                </el-table>
                <el-button
                  slot="reference"
                  class="camera"
                  circle
                  icon="el-icon-video-camera-solid"
                  >
                </el-button>
              </el-popover>
          </div>
        </el-card>
      </el-main>
    </el-container>
  </div>
</template>

<script>
import LeaderLine from 'leader-line'
import moment from 'moment'

export default {
  name: 'TestComponent',
  props: {},
  data() {
    let cameraPos = []
    let mapImageUrl = ''
    let fileList = []
    let serverUrl = ''
    let taskStatus = [
      '未开始',
      '正在追踪',
      '已完成'
    ]
    let taskIndex = 0
    let taskFlag = false
    let timeout = 40
    let taskID = -1
    let traceImage = require('./status.jpeg')
    let objectImgWidth = '245px'
    let objectImgHeight = '300px'
    let objectPicUrl = ''
    let isSubmitStatus = false
    let timer = null
    let taskStartTime = 0
    let taskEndTime = 0
    let queryTaskStatus = false
    let resultData = 0
    let cameraOrder = []
    let leaderLineArray = []
    let cameraGridData = []

      return {cameraPos, mapImageUrl, fileList, serverUrl, taskID, taskStatus, taskIndex,  timeout, traceImage, taskFlag, objectImgWidth, objectImgHeight, objectPicUrl, isSubmitStatus, timer, queryTaskStatus, taskStartTime, taskEndTime, resultData, cameraOrder, leaderLineArray, cameraGridData,
      pickerOptions: {
          shortcuts: [{
            text: '最近一周',
            onClick(picker) {
              const end = new Date();
              const start = new Date();
              start.setTime(start.getTime() - 3600 * 1000 * 24 * 7);
              picker.$emit('pick', [start, end]);
            }
          }, {
            text: '最近一个月',
            onClick(picker) {
              const end = new Date();
              const start = new Date();
              start.setTime(start.getTime() - 3600 * 1000 * 24 * 30);
              picker.$emit('pick', [start, end]);
            }
          }, {
            text: '最近三个月',
            onClick(picker) {
              const end = new Date();
              const start = new Date();
              start.setTime(start.getTime() - 3600 * 1000 * 24 * 90);
              picker.$emit('pick', [start, end]);
            }
          }]
        },
        timeValue: ''
      }
  },

  mounted(){
    this.$refs.leftMenuCard.$el.style.minheight = this.$refs.mapImage.$el.clientHeight + 'px'
  },

  created(){
    console.log('created')
    this.mapImageUrl = this.mapInitiation()
    // console.log('mapImageUrl', this.mapImageUrl)
    this.cameraPos = this.cameraInitiation()
    // console.log('cameraPos', this.cameraPos)
  },

  destroyed(){
    clearInterval(this.timer)
    this.timer = null
  },

  methods:{
    test(){
      // console.log('time', this.timeValue)
      // console.log('start v', this.timeValue[0].valueOf())
      // console.log('start v', this.timeValue[0])
      // console.log('end v', this.timeValue[1].valueOf())
      // console.log('end v', this.timeValue[1])
      // console.log('start', moment(this.timeValue[0]).format('YYYY-MM-DD HH:MM:SS'))
      // console.log('end', moment(this.timeValue[1]).format('YYYY-MM-DD HH:MM:SS'))
      // console.log('test', typeof(moment(this.timeValue[0]).format('YYYY-MM-DD HH:MM:SS')))
      // console.log('test', typeof('2023-09-14 09:59:33'))
      // console.log('before', this.isSubmitStatus)
      // this.isSubmitStatus = !this.isSubmitStatus
      // console.log('after', this.isSubmitStatus)
      // moment
      // this.trackObject();
    },

    cameraInitiation(){
      let camera = [
        [280, 100],
        [560, 0],
        [595, 390],
        [725, 20]
      ]

      return camera
    },

    mapInitiation(){
      return require('./map.png')
    },

    trackObject(){
      console.log('trackobject')

      let leftToRight = [{ x: 66, y: 34}, { x: 0, y: 34}]
      let rightToLeft = [{ x: 0, y: 34}, { x: 66, y: 34}]
      let upTodown    = [{ x: 34, y: 67}, { x: 34, y: 0}]
      let downToUp    = [{ x: 34, y: 0}, { x: 34, y: 67}]
      let posOffset = null
      let cameraDom = [0,
      document.getElementById('1'),
      document.getElementById('2'),
      document.getElementById('3'),
      document.getElementById('4'),]

    for(let i = 0; i < this.cameraOrder.length - 1; i++){
      let tmpX = cameraDom[this.cameraOrder[i]].offsetLeft - cameraDom[this.cameraOrder[i + 1]].offsetLeft
      let tmpY = cameraDom[this.cameraOrder[i]].offsetTop - cameraDom[this.cameraOrder[i + 1]].offsetTop
      if(Math.abs(tmpX) >= Math.abs(tmpY)){
        if(tmpX > 0){
          posOffset = rightToLeft
        }
        else{
          posOffset = leftToRight
        }
      }
      else{
        if(tmpY > 0){
          posOffset = downToUp
        }
        else{
          posOffset = upTodown
        }
      }
      this.leaderLineArray.push(new LeaderLine(LeaderLine.pointAnchor(cameraDom[this.cameraOrder[i]], posOffset[0]),
      LeaderLine.pointAnchor(cameraDom[this.cameraOrder[i + 1]], posOffset[1]),
      {color: '#338fff', size: 8}))
    }

      return true
    },

    destroyLeaderLine(){
      if(this.leaderLineArray.length != 0){
        for(let i = 0; i < this.leaderLineArray.length; i++){
          this.leaderLineArray[i].remove()
        }
      }
    },

    destroyTableContent(){
      if(this.cameraGridData != 0){
        this.cameraGridData = []
      }
    },

    /* synchronize create task */
    async uploadAttachment(params){
      await this.$axios.post('http://192.168.1.242:8760/api/file/file/anyone/upload', params,{
        headers:{
          'Content-Type': 'multipart/form-data'
        }
      }).then(response=>{
        console.log('success upload', response)
        this.objectPicUrl = response.data.data.url.substring(response.data.data.url.length + 1, response.data.data.url.indexOf("group"))
      }).catch(error=>{
        console.log('error upload', error)
        this.isSubmitStatus = !this.isSubmitStatus
        this.taskIndex = 0
        this.taskFlag = false
      });
    },

    async releaseTask(params){
      // console.log('release task', params)
      await this.$axios.post('http://192.168.1.242:8760/api/task/release/task', params, {
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded'
        }
      }).then(response=>{
        console.log('success release', response)
        this.taskID = response.data.data
      }).catch(error=>{
        console.log('error release', error)
        this.isSubmitStatus = !this.isSubmitStatus
        this.taskIndex = 0
        this.taskFlag = false
        if(this.taskID != -1){
          this.taskID = -1
        }
      });
    },

    async createTask(tmpFileList){
      // console.log('createTask')
      // console.log('tmpFileList', tmpFileList)

      this.isSubmitStatus = !this.isSubmitStatus
      this.taskIndex = 1
      this.taskFlag = true
      // 创建追踪任务前先上传追踪者图片,第一步准备接口参数
      let formData = new FormData()
      formData.append('file', tmpFileList[0].raw)
      formData.append('bizType', 'filetransfer')
      formData.append('bucket', 'filetransfer')
      formData.append('storageType', 'FAST_DFS')
      // 使用同步请求上传附件
      await this.uploadAttachment(formData)

      // console.log('objectPicUrl', this.objectPicUrl)

      // 发布任务
      let params = new FormData()
      params.append('end', moment(this.timeValue[1]).format('YYYY-MM-DD HH:MM:SS'))
      params.append('start', moment(this.timeValue[0]).format('YYYY-MM-DD HH:MM:SS'))
      params.append('url', this.objectPicUrl)

      await this.releaseTask(params)
      // console.log('create task down ...................')
    },

    dealTrackData(){
      console.log('deal', this.resultData)
      let tmpDeal = this.resultData[0][0]
      let tmpMap = new Map()
      let index = 1
      let t = 0
      let start = 0
      let end = 0

      if(this.cameraOrder.length != 0){
        this.cameraOrder = []
      }

      this.cameraOrder.push(parseInt(this.resultData[0][0]))
      for(let i = 1; i < this.resultData.length; i++){
        if(this.resultData[i][0] != tmpDeal){
          tmpMap.set(parseInt(tmpDeal), index)
          index = 1
          tmpDeal = this.resultData[i][0]
          this.cameraOrder.push(parseInt(this.resultData[i][0]))
        }
        else{
          index++
        }
      }
      tmpMap.set(parseInt(this.resultData[this.resultData.length - 1][0]), index)

      for(let i = 0; i < this.cameraOrder.length; i++){
        let s1 = this.resultData[t].substring(13, 15)
        let s2 = this.resultData[t].substring(16, 18)
        let s3 = this.resultData[t].substring(19)
        start = this.resultData[t].substring(2, 12) + ' ' + s1 + ':' + s2 + ':' + s3

        t += tmpMap.get(this.cameraOrder[i])

        s1 = this.resultData[t - 1].substring(13, 15)
        s2 = this.resultData[t - 1].substring(16, 18)
        s3 = this.resultData[t - 1].substring(19)
        end = this.resultData[t - 1].substring(2, 12) + ' ' + s1 + ':' + s2 + ':' + s3

        let tmpCLass = [{
          startTime: start,
          endTime: end
        }]

        this.cameraGridData.push(tmpCLass)
      }
      console.log('cameraGrid', this.cameraGridData)
    },

    statusUpdate(){
      console.log('statusUpdate')

      if(this.taskStatus[this.taskIndex] == '已完成'){
        this.$message({
          message: '任务已完成！请查看视频轨迹！',
          type: 'success'
        })
        this.taskFlag = false
        this.trackObject()
      }
      else{
        if(this.taskID == -1){
          this.taskEndTime = parseInt(new Date().getTime() / 1000)

          if(this.taskEndTime - this.taskStartTime >= this.timeout){
            this.taskIndex = 0
            this.taskFlag = false
            this.isSubmitStatus = false
            this.$message.error('已超时！任务还未完成！请重新提交任务！')
            this.clearTimerFromQueryTask()
          }
          else{
            this.$message.error('刷新成功！任务还未完成！请稍后！')
          }
        }
        else{
          this.getTaskResult()
        }
      }
    },

    getTaskResult(){
      let params = new FormData()
      params.append('taskId', this.taskID)

      this.$axios.post("http://192.168.1.242:8760/api/task/release/reidImgRes", params,{
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded'
        }
      })
      .then(response=>{
        console.log('query success', response)
        this.taskIndex = 2
        this.taskFlag = false
        this.isSubmitStatus = !this.isSubmitStatus
        this.resultData = response.data.data[0].reidResImgs
        this.dealTrackData()
        this.clearTimerFromQueryTask()
        this.statusUpdate()
      }).catch(error=>{
        console.log('error', error)
        this.$message.error('刷新成功！任务还未完成！请稍后！')
      });
    },

    handleUploadFileChange(file, fileList){
      this.taskIndex = 0
      this.fileList = fileList
      this.traceImage = file.url
    },

    handleUploadFileRemove(file, fileList){
      this.fileList = fileList
      if(this.fileList.length > 0){
        this.traceImage = this.fileList[0].url
      }
      else{
        this.traceImage = require('./status.jpeg')
      }
    },

    setTimerToQueryTask(){
      if(this.timer != null){
        this.clearTimerFromQueryTask()
      }
      this.taskStartTime = parseInt(new Date().getTime() / 1000)
      this.timer = setInterval(this.statusUpdate, 5000)
    },

    clearTimerFromQueryTask(){
      clearInterval(this.timer)
      this.timer = null
    },

    submitUpload(){
      console.log('submit task')
      if(this.fileList.length <= 0){
        this.$message.error('开始追踪任务前请提交追踪者照片！')
        return
      }

      if(this.fileList.length >= 2){
        this.$message.error('每次追踪只可以追踪一张人像，请先删除多余的人像图片！')
        return
      }

      if(this.timeValue.length <= 0){
        this.$message.error('开始追踪任务前请选择追踪时间段！')
        return
      }

      if(this.cameraOrder.length != 0){
        this.cameraOrder = []
        this.destroyLeaderLine()
        this.destroyTableContent()
      }

      this.$message.success('任务已提交！请稍后！')

      this.setTimerToQueryTask()

      this.createTask(this.fileList)
    },
  },
}
</script>

<style scoped>
#test{
  font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
}

/* left menu */
#leftTaskTitle{
  font-size: 24px;
}

#leftMenu{
  padding: 20px;
}

.menuInterval{
  margin-top: 30px;
}

/* map */
#mapImageCard{
  width: 99%;
  height: calc(100vh - 130px);
  background-image: url("./map.png");
  background-size: cover;
  background-repeat: no-repeat;
}

/* camera */
.camera{
  position: relative;
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
