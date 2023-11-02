<template>
  <el-dialog
    :close-on-click-modal="false"
    :close-on-press-escape="true"
    :title="title"
    :type="type"
    :visible.sync="isVisible"
    :width="width"
    top="50px"
  >
<!--    底部的取消与确定键-->
    <div
      slot="footer"
      class="dialog-footer"
    >
      <el-button
        plain
        type="warning"
        @click="isVisible = false"
      >
        {{ $t("common.cancel") }}
      </el-button>
      <el-button
        plain
        type="primary"
        @click="submitForm"
      >
        {{ $t("common.confirm") }}
      </el-button>
    </div>
<!--    信息表格-->
    <el-form
      ref="form"
      :model="encState"
      :rules="rules"
      label-position="right"
      label-width="100px"
    >
      <el-form-item
        :label="$t('table.camera.camId')"
        prop="id"
      >
        <el-input
          v-model="encState.id"
          :disabled="type==='edit'"
          type=""
          placeholder="摄像头ID"
        />
      </el-form-item>
      <el-form-item
        :label="$t('table.camera.camName')"
        prop="camName"
      >
        <el-input
          v-model="encState.camName"
          type=""
          placeholder="摄像头名称"
        />
      </el-form-item>
      <el-form-item
        :label="$t('table.camera.camPosX')"
        prop="camPosX"
      >
        <el-input
          v-model="encState.camPosX"
          type=""
          placeholder="摄像头X坐标"
        />
      </el-form-item>
      <el-form-item
          :label="$t('table.camera.camPosY')"
          prop="camPosY"
      >
        <el-input
            v-model="encState.camPosY"
            type=""
            placeholder="摄像头Y坐标"
        />
      </el-form-item>
      <el-form-item
        :label="$t('table.camera.camStatus')"
        prop="camState"
      >
        <el-input
          v-model="encState.camStatus"
          type=""
          placeholder="摄像头状态"
        />
      </el-form-item>
    </el-form>
  </el-dialog>
</template>
<script>
import cameraApi from "@/api/Camera.js";

export default {
    name: "CamEdit",
    components: {  },
    props: {
        dialogVisible: {
            type: Boolean,
            default: false
        },
        type: {
            type: String,
            default: "add"
        }
    },
    data() {
        return {
            encState: this.initencState(),
            screenWidth: 0,
            width: this.initWidth(),
            // rules: {
            //     nodeIp: [
            //         {required: true, message: this.$t("rules.require"), trigger: "blur"},
            //         { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
            //     ],
            //     nodeName: [
            //         {required: true, message: this.$t("rules.require"), trigger: "blur"},
            //         { min: 1, max: 255, message: '最多不能超过255字符', trigger: "blur"}
            //     ],
            //     nodePort: [
            //         { max: 255, message: '最多不能超过255字符', trigger: "blur"}
            //     ],
            // }
        };
    },
    computed: {
        isVisible: {
            get() {
                return this.dialogVisible;
            },
            set() {
                this.close();
                this.reset();
            }
        },
        title() {
            return this.$t("common." + this.type);
        }
    },
    watch: {},
    mounted() {
        window.onresize = () => {
            return (() => {
                this.width = this.initWidth();
            })();
        };
    },
    methods: {
        initencState() {
            return {
                id: "",
                camName: '',
                camPosX: '',
                camPosY: '',
                camStatus: ''

            };
        },
        initWidth() {
            this.screenWidth = document.body.clientWidth;
            if (this.screenWidth < 991) {
                return "90%";
            } else if (this.screenWidth < 1400) {
                return "45%";
            } else {
                return "800px";
            }
        },
        setencState(val) {
            const vm = this;
            if (val) {
                vm.encState = { ...vm.encState, ...val };
            }
        },
        close() {
            this.$emit("close");
        },
        reset() {
            // 先清除校验，再清除表单，不然有奇怪的bug
            this.$refs.form.clearValidate();
            this.$refs.form.resetFields();
            this.encState = this.initencState();
        },
        submitForm() {
            const vm = this;
            this.$refs.form.validate(valid => {
                if (valid) {
                    vm.editSubmit();
                } else {
                    return false;
                }
            });
        },
        editSubmit() {
            const vm = this;
            if (vm.type === "add") {
                vm.update();
            } else {
                vm.save();
            }
        },
        save() {
            const vm = this;
            cameraApi.save(this.encState).then(response => {
                const res = response.data;
                if (res.isSuccess) {
                    vm.isVisible = false;
                    vm.$message({
                        message: vm.$t("tips.createSuccess"),
                        type: "success"
                    });
                    vm.$emit("success");
                }
            });
        },
        update() {
          const vm = this;
          cameraApi.update(this.encState).then(response => {
            const res = response.data;
            if (res.isSuccess) {
              vm.isVisible = false;
              vm.$message({
                message: vm.$t("tips.createSuccess"),
                type: "success"
              });
              vm.$emit("success");
            }
          });
        }
    }
};
</script>
<style lang="scss" scoped></style>
